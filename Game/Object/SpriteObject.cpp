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
		//states.transform *= getTransform();

		sprite.setPosition(getPosition());
		sprite.setRotation(getRotation());
		sprite.setScale(getScale());
		target.draw(sprite, states);

		if (Settings::show_hitboxes)
		{
			Shape::createRectangle(getCollisionRect(), hitbox_vertices);
			target.draw(hitbox_vertices, 5, sf::LinesStrip, states);
		}
	}
	SpriteObject::SpriteObject()
		: hitbox({ -0.5f, -0.5f }, { 0.5f, 0.5f }) 
	{
		for (auto& vert : hitbox_vertices)
			vert.color = { 0, 0, 255 };
	}

	bool SpriteObject::touches(const PhysicalRect& rect) const
	{
		return Collision::areIntersected(rect, getCollisionRect());
	}
	RepulsionResult SpriteObject::getRepulsionVector(const PhysicalRect& rect) const
	{
		return Collision::collide(rect, getPhysicalRect());
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
		if (physical_rect.min.x > physical_rect.max.x)
			std::swap(physical_rect.min.x, physical_rect.max.x);
		if (physical_rect.min.y > physical_rect.max.y)
			std::swap(physical_rect.min.y, physical_rect.max.y);
		return physical_rect;
	}
	Rect SpriteObject::getCollisionRect() const
	{
		Rect result{
			hitbox.min * getScale() + getPosition(),
			hitbox.max * getScale() + getPosition()
		};
		if (result.min.x > result.max.x)
			std::swap(result.min.x, result.max.x);
		if (result.min.y > result.max.y)
			std::swap(result.min.y, result.max.y);
		return result;
	}
}