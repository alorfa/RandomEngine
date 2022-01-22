#pragma once

#include <filesystem>
#include <SFML/Graphics.hpp>
#include <RandomEngine/API/Graphics/Camera.hpp>
#include "RandomEngine/API/GlobalData.hpp"

namespace random_engine
{
	class AbortEventProcessing {};

	class Application
	{
		float base_delta = 0.f;
		float delta = 0.f;

		sf::Event e = sf::Event();
		sf::RenderTarget& target;

		sf::Clock clock;
	protected:
		float time_speed = 1.f;

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
		sf::Window& window;
		Camera& camera;
		std::filesystem::path& res;

		Application(GlobalData& data);
		virtual ~Application() = default;

		void run();
	};
}