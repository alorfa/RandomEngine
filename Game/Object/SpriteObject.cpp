#include "SpriteObject.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include <RandomEngine/API/Auxiliary/print_vectors.hpp>
#include <RandomEngine/API/Graphics/Shape.hpp>
#include <RandomEngine/API/Math/RepulsionResult.hpp>
#include <RandomEngine/API/Math/CollisionFunctions.hpp>
#include "Game/Player.hpp"
#include "Game/Settings.hpp"

namespace game
{
	void SpriteObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(sprite, states);

		if (Settings::show_hitboxes)
		{
			Shape::createRectangle(hitbox, hitbox_vertices);
			target.draw(hitbox_vertices, 5, sf::LinesStrip, states);
		}
	}
	SpriteObject::SpriteObject()
		: hitbox({ -0.5f, -0.5f }, { 0.5f, 0.5f }) 
	{
		for (auto& vert : hitbox_vertices)
			vert.color = { 0, 0, 255 };
	}

	bool SpriteObject::touches(const Player& p) const
	{
		Rect player(p.getPosition() - p.getScale() * 0.5f);
		player.max = player.min + p.getScale();

		return Collision::areIntersected(player, getCollisionRect());
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
		physical_rect.center = getPosition();
		physical_rect.min = hitbox.min * getScale() + getPosition();
		physical_rect.max = hitbox.max * getScale() + getPosition();
		physical_rect.movement = getPosition() - getPrevPos();
		return physical_rect;
	}
	Rect SpriteObject::getCollisionRect() const
	{
		return Rect{
			hitbox.min * getScale() + getPosition(),
			hitbox.max * getScale() + getPosition()
		};
	}
}