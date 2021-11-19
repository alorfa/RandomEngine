#include "Keyboard.hpp"
#include <SFML/Window/Window.hpp>

namespace random_engine
{
	bool Keyboard::isPressed(Key key)
	{
		return window &&
			window->hasFocus() &&
			sf::Keyboard::isKeyPressed(key);
	}
}