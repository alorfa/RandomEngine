#include "Application.hpp"

#include <iostream>
#include <RandomEngine/API/System/Mouse.hpp>
#include <RandomEngine/API/System/Keyboard.hpp>

namespace random_engine
{
	vec2 Application::handleNativeCameraSize(const vec2& size) const
	{
		return vec2(size.x * aspectRatio(), size.y);
	}
	float Application::handleDelta(float base_delta) const
	{
		return Math::clamp(base_delta * time_speed, 0.f, 1.f);
	}
	void Application::engineError(const sf::String& title)
	{
		std::cerr << title.toAnsiString() << std::endl;
	}
	void Application::exit()
	{
		appEnd();
		window.close();
	}
	float Application::aspectRatio() const
	{
		const vec2 size = window.getSize();
		return size.x / size.y;
	}
	Application::Application()
		: window(renderwindow), camera(window)
	{

	}
	void Application::run(const sf::Vector2u window_size, const sf::String& title,
		uint32_t style, const sf::ContextSettings& settings)
	{
		window.create(sf::VideoMode(window_size.x, window_size.y), title, style, settings);

		if (not window.isOpen())
		{
			engineError("Window cannot be created!");
			return;
		}
		Mouse::window = &window;
		Mouse::camera = &camera;
		Keyboard::window = &window;
		Camera::window = &window;

		window.setFramerateLimit(120);

		appInit();
		loadResources();
		startGame();

		while (window.isOpen())
		{
			base_delta = clock.restart().asSeconds();
			delta = handleDelta(base_delta);

			// event loop
			while (window.pollEvent(e))
			{
				switch (e.type)
				{
				case sf::Event::Closed:
					exit();
					break;
				case sf::Event::Resized:
					camera.updateNativeSize();
					break;
				}
				handleEvent(e);
			}
			update(base_delta, delta);
			renderwindow.setView(camera.getSFMLView());
			draw(renderwindow);
			window.display();
		}
	}
}