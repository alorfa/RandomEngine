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
	RepulsionResult SpriteObject::getRepulsionVector(const Player& p) const
	{
		return Collision::collide(p.getPhysicalRect(), getPhysicalRect());
	}
	void SpriteObject::load(const std::filesystem::path& path)
	{
		sprite.setTexture(textureLoader.load(path));
	}
	void SpriteObject::setArea(const vec2& p1, const vec2& p2)
	{
		sprite.setArea(p1, p2);
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