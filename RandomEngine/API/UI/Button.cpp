#include "Button.hpp"
#include "RandomEngine/API/Graphics/Shape.hpp"
#include "RandomEngine/API/System/Mouse.hpp"
#include "RandomEngine/API/GlobalData.hpp"
#include "RandomEngine/API/Application.hpp"

namespace random_engine
{
	void Button::handleEvents(const sf::Event& e)
	{
		Rect hitbox{
			getPosition() - getScale() * 0.5f,
			getPosition() + getScale() * 0.5f
		};
		switch (e.type)
		{
		case sf::Event::MouseButtonPressed:
			if (Collision::areIntersected(Mouse::getPosition(*camera), hitbox)) {
				mouse_has_pressed = true;
				throw AbortEventProcessing();
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (mouse_has_pressed and Collision::areIntersected(Mouse::getPosition(*camera), hitbox))
			{
				onClick(*owner);
				mouse_has_pressed = false;
				throw AbortEventProcessing();
			}
			break;
		}
	}
	void Button::update(float delta)
	{
	}
}