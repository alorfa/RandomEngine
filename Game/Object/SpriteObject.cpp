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
		RepulsionResult handleRects(const Vec2& p1, const Vec2& p2,
			const Vec2& r1, const Vec2& r2, const Player& player, const Object& obj)
		{
			RepulsionResult result;
			result.touches = (p2.x >= r1.x &&
				p1.x <= r2.x &&
				p2.y >= r1.y &&
				p1.y <= r2.y);
			if (result.touches)
			{
				result.direction.y = (obj.getPosition().y - obj.getPrevPos().y) * 100.f;
				if (p2.y > r2.y)
				{
					result.offset.y = r2.y - p1.y;
				}
				if (p1.y < r1.y)
				{
					result.offset.y = r1.y - p2.y;
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
		const Vec2 p1 = p.getPosition() - p.getScale() * 0.5f;
		const Vec2 p2 = p1 + p.getScale();

		const Vec2 r1 = getPosition() - getScale() * 0.5f;
		const Vec2 r2 = r1 + getScale();

		return handleRects(p1, p2, r1, r2, p, *this);
	}
	void SpriteObject::load(const std::filesystem::path& path)
	{
		sprite.setTexture(textureLoader.load(path));
	}
}