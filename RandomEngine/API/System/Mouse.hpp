#pragma once

#include <RandomEngine/API/Graphics/Camera.hpp>
#include <SFML/Window/Mouse.hpp>

namespace random_engine
{
	class Mouse
	{
	public:
		using Button = sf::Mouse::Button;

		static vec2 getPosition(const Camera& relative_to);
		static vec2 getPosition();

		static bool isPressed(Button button);
	};
}