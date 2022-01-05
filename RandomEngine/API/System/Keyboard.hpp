#pragma once

#include <SFML/Window/Keyboard.hpp>

namespace random_engine
{
	class Keyboard
	{
	public:
		using Key = sf::Keyboard::Key;

		static bool isPressed(Key key);
	};
}