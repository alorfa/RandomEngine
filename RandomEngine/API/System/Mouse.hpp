#pragma once

#include <RandomEngine/API/Graphics/Camera.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Mouse.hpp>

namespace random_engine
{
	class Application;

	class Mouse
	{
		static const sf::Window* window;
		static const Camera* camera;

		friend class Application;
	public:
		using Button = sf::Mouse::Button;

		static Vec2 getPosition(const Camera& relative_to);
		static Vec2 getPosition();

		static bool isPressed(Button button);

		static void setDefaultCamera(const Camera& camera);
	};
}