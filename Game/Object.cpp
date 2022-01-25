#include "Object.hpp"
#include <RandomEngine/API/System/Mouse.hpp>
#include <RandomEngine/API/Graphics/Shape.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace game
{
	void Object::update(float delta)
	{
		prev_position = getPosition();
		direction = (getPosition() - prev_position) * 100.f;
	}
	void Object::moveByTrigger(const vec2& offset)
	{
		move(offset);
	}
	void Object::rotateByTrigger(float deg)
	{
		rotate(deg);
	}
	void Object::scaleByTrigger(const vec2& factor)
	{
		scale(factor);
	}
	void Object::drawHitbox(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		Shape::createRectangle(hitbox, hitbox_vertices);
		target.draw(hitbox_vertices, 5, sf::LineStrip, states);
	}
}