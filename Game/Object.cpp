#include "Object.hpp"
#include <RandomEngine/API/System/Mouse.hpp>

namespace game
{
	void Object::update(float delta)
	{
		prev_position = getPosition();
		direction = (getPosition() - prev_position) * 100.f;
	}
}