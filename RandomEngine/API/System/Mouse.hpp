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

		static vec2 getOffset(const vec2& camera_size, const ivec2& pixel_offset);

		static bool isPressed(Button button);
	};
}