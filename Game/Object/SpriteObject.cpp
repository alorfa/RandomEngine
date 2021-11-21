#include "SpriteObject.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "SpriteObject.hpp"

#include "Game/Player.hpp"
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include <RandomEngine/API/Auxiliary/print_vectors.hpp>

#include <RandomEngine/API/Math/RepulsionResult.hpp>
#include <RandomEngine/API/Math/CollisionFunctions.hpp>

namespace game
{
	namespace
	{
		RepulsionResult handleRects(AxisAlignedBox const& p, AxisAlignedBox const& r, 
									const Player& player, const Object& obj)
		{
			RepulsionResult result;
			result.touches = Collision::areIntersected(p, r);
			if (result.touches)
			{
				// find touching edge: top left right bottom
				//          +++++++
				//          +++R+++
				//          +++++++
				//       ***
				//       *P*
				//       ***
				//       P,R are centers

				Vec2 const scale = p.max - p.min + r.max - r.min;
				Vec2 const p2o = Vec2(obj.getPosition() - player.getPosition())/scale;

				result.direction = (obj.getPosition() - obj.getPrevPosition());
				if(fabs(p2o.x) >= fabs(p2o.y))
				{ // left or right
					if(p.max.x > r.max.x)
						result.offset.x = r.max.x - p.min.x;
					else if(p.min.x < r.min.x)
						result.offset.x = r.min.x - p.max.x;
					result.direction.x *= 50.f; // little bounce
					result.direction.y = player.direction.y;
				}
				else
				{ // top or bottom
					if(p.max.y > r.max.y)
					{
						result.offset.y = r.max.y - p.min.y;
						if(result.direction.y > 0.1f)
						{ // bouncy surface
							result.direction.y *= 100.f;
							result.offset.x = 0.;
							result.direction.x *= 20; // friction
						}
						else
						{  // sticky surface
							result.offset.x = result.direction.x;
							result.direction.x = 0.f;
						}
					}
					else if(p.min.y < r.min.y)
					{
						result.offset.y = r.min.y - p.max.y;
						if(result.direction.y < -0.1f)
							result.direction.y *= 100.f;
					}
				}
			}
			return result;
		}
	}
	void SpriteObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		sprite.setPosition(getPosition());
		sprite.setScale(getScale());
		sprite.setRotation(getRotation());

		target.draw(sprite);
	}

	bool SpriteObject::touches(const Player& p) const
	{
		auto player = AxisAlignedBox::fromCenterScale(p.getPosition(), p.getScale() * 0.5f);
		auto obj = AxisAlignedBox::fromCenterScale(getPosition(), getScale() * 0.5f);
		return Collision::areIntersected(player, obj);
	}

	RepulsionResult SpriteObject::getRepulsionVector(const Player& p) const
	{
		auto player = AxisAlignedBox::fromCenterScale(p.getPosition(), p.getScale() * 0.5f);
		auto obj = AxisAlignedBox::fromCenterScale(getPosition(), getScale() * 0.5f);
		return handleRects(player, obj, p, *this);
	}

	void SpriteObject::load(const std::filesystem::path& path)
	{
		sprite.setTexture(textureLoader.load(path));
	}
}