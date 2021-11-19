#include "Object.hpp"
#include <RandomEngine/API/System/Mouse.hpp>

namespace game
{
	void Object::update(float delta)
	{
		prev_position = getPosition();
		setPosition(Mouse::getPosition());
	}
}