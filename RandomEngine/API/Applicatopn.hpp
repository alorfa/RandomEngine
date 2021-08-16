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
	public:
		Camera native_camera;
	protected:
		sf::Window& window;

		float time_speed = 1.f;

		sf::Color clear_color;
		sf::Transformable camera;

		virtual void appInit() = 0;
		virtual vec2 handleNativeCameraSize(const vec2& native_camera_size) const;
		virtual void handleEvent(const sf::Event& event) = 0;
		virtual void everyFrame(float base_delta, float delta) = 0;
		virtual void draw(sf::RenderTarget& window) const = 0;
		virtual void appEnd() = 0;

		virtual void engineError(const sf::String& title);
		void exit();

		float aspectRatio() const;
		const Camera& nativeCamera() const;
	public:
		std::filesystem::path res;

		Application();
		virtual ~Application() = default;

		void run(const sf::Vector2u window_size, const sf::String& title, uint32_t style = sf::Style::Default, 
			const sf::ContextSettings& settings = sf::ContextSettings());


	};
}