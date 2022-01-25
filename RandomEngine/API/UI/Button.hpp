#pragma once

#include <SFML/Window/Event.hpp>
#include "RandomEngine/API/UI/UIComponent.hpp"

namespace random_engine
{
	class Scene;
	class Camera;

	class Button : public UIComponent
	{
		bool mouse_has_pressed = false;
	public:
		using Event = void (*)(Scene& scene);

		Event onClick = nullptr;

		void handleEvents(const sf::Event& e) override;
		void update(float delta) override;
	};
}