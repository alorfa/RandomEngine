#pragma once

#include <SFML/Window/Keyboard.hpp>

namespace sf
{
	class Window;
}
namespace random_engine
{
	class Application;

	class Keyboard
	{
		inline static const sf::Window* window = nullptr;

		friend class Application;
	public:
		using Key = sf::Keyboard::Key;

		static bool isPressed(Key key);
	};
}