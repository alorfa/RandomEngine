#pragma once

#include <filesystem>
#include <SFML/Graphics.hpp>
#include <RandomEngine/API/Graphics/Camera.hpp>

namespace random_engine
{
	class Application
	{
		float base_delta = 0.f;
		float delta = 0.f;

		sf::Event e = sf::Event();
		sf::RenderWindow renderwindow;

		sf::Clock clock;
	protected:
		sf::Window& window;

		float time_speed = 1.f;

		Camera camera;

		virtual void appInit() = 0;
		virtual void loadResources() = 0;
		virtual void startGame() = 0;
		virtual vec2 handleNativeCameraSize(const vec2& native_camera_size) const;
		virtual float handleDelta(float base_delta) const;
		virtual void handleEvent(const sf::Event& event) = 0;
		virtual void update(float base_delta, float delta) = 0;
		virtual void draw(sf::RenderTarget& window) const = 0;
		virtual void appEnd() = 0;

		virtual void engineError(const sf::String& title);
		void exit();

		float aspectRatio() const;
	public:
		std::filesystem::path res;

		Application();
		virtual ~Application() = default;

		void run(const sf::Vector2u window_size, const sf::String& title, uint32_t style = sf::Style::Default, 
			const sf::ContextSettings& settings = sf::ContextSettings());
	};
}