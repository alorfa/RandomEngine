#pragma once

#include <RandomEngine/API/UI/UIComponent.hpp>
#include <RandomEngine/API/Math/vec2.hpp>

using namespace random_engine;

namespace game
{
	class HotkeyHandler : public UIComponent
	{
		bool is_pressed = false;
		ivec2 prev_mouse_pos;
	public:
		void updateComponentsAlignment() override;
		void handleEvents(const sf::Event& e) override;
		void update(float delta) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}