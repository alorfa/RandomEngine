#pragma once

#include <RandomEngine/API/Graphics/Camera.hpp>
#include <SFML/Window/Window.hpp>

namespace random_engine
{
	class Application;

	class Mouse
	{
		static const sf::Window* window;
		static const Camera* camera;

		friend class Application;
	public:
		static vec2 getPosition(const Camera& relative_to);
		static vec2 getPosition();

		static void setDefaultCamera(const Camera& camera);
	};
}