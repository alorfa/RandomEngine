#include "Object.hpp"
#include <RandomEngine/API/System/Mouse.hpp>

namespace game
{
	void Object::update(float delta)
	{
		prev_position = getPosition();
<<<<<<< HEAD
		setPosition(Mouse::getPosition());
		direction = (getPosition() - prev_position) * 100.f;
=======
        setPosition(Mouse::getPosition());
        direction = (getPosition() - prev_position) * 10.f;
>>>>>>> collision-fix
	}
}