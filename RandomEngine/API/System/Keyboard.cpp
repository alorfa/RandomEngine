#include "Keyboard.hpp"
#include <SFML/Window/Window.hpp>
#include "RandomEngine/API/Application.hpp"

namespace random_engine
{
	bool Keyboard::isPressed(Key key)
	{
		const auto& window = GlobalData::getInstance().window;
		return window.hasFocus() &&
			sf::Keyboard::isKeyPressed(key);
	}
}