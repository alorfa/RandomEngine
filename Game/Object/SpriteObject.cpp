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
        RepulsionResult handleRects(Rect const& p, Rect const& r,
            const Player& player, const Object& obj)
        {
            RepulsionResult result;
            result.touches = Collision::areIntersected(p, r);
            if(result.touches)
            {
                // find touching edge: top left right bottom
                //          +++++++
                //          +++R+++
                //          +++++++
                //       ***
                //       *P*
                //       ***
                //       P,R are centers

                vec2 const scale = p.max - p.min + r.max - r.min;
                vec2 const p2o = vec2(obj.getPosition() - player.getPosition()) / scale;

                // (x, y) <=> (a*t, b*t), (a*t, -b*t)
                //  
                // (x/a, y/b) <=> (t, t), (t, -t)
                //  upper:   y/b >=  fabs(x/a)
                //  lower:   y/b <= -fabs(x/a)
                //  righter: x/a >   fabs(y/b)
                //  lefter:  x/a <  -fabs(y/b)

                if(fabs(p2o.x) >= fabs(p2o.y))
                { // left or right
                    if(p.max.x > r.max.x)
                    {
                        result.offset.x = r.max.x - p.min.x;
                        result.normal.x = 1.;
                    }
                    else if(p.min.x < r.min.x)
                    {
                        result.offset.x = r.min.x - p.max.x;
                        result.normal.x = -1.;
                    }
                    result.direction.x *= 50.f; // little bounce
                    result.direction.y = player.direction.y;
                }
                else
                { // top or bottom
                    if(p.max.y > r.max.y)
                    {
                        result.offset.y = r.max.y - p.min.y;
                        result.normal.y = 1.;
                    }
                    else if(p.min.y < r.min.y)
                    {
                        result.offset.y = r.min.y - p.max.y;
                        result.normal.y = -1.;
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
		Rect player(p.getPosition() - p.getScale() * 0.5f);
		player.max = player.min + p.getScale();
		Rect obj(getPosition() - getScale() * 0.5f);
		obj.max = obj.min + getScale();

		return Collision::areIntersected(player, obj);
	}
	RepulsionResult SpriteObject::getRepulsionVector(const Player& p, bool noMovement /*= false*/) const
	{
        auto const& sr = getPhysicalRect();
        auto const& pr = p.getPhysicalRect();

		return noMovement? handleRects(pr, sr, p, *this): Collision::collide(pr, sr);
	}
	void SpriteObject::load(const std::filesystem::path& path)
	{
		sprite.setTexture(textureLoader.load(path));
	}
	const PhysicalRect& SpriteObject::getPhysicalRect() const
	{
		physical_rect.direction = direction;
		physical_rect.min = getPosition() - getScale() * 0.5f;
		physical_rect.max = physical_rect.min + getScale();
		physical_rect.center = getPosition();
		physical_rect.movement = getPosition() - getPrevPos();
		return physical_rect;
	}
}