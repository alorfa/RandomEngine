#pragma once

#include <SFML/Window/Event.hpp>
#include "RandomEngine/API/UI/UIComponent.hpp"
#include "RandomEngine/API/Graphics/Sprite.hpp"

namespace random_engine
{
	class Scene;

	class Button : public UIComponent
	{
		bool mouse_has_pressed = false;
	public:
		Sprite sprite;

		using Event = void (*)(Button& self);

		Event onPressed = nullptr;
		Event onReleased = nullptr;

		void updateComponentsAlignment();
		void handleEvents(const sf::Event& e) override;
		void update(float delta) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}