#include "Button.hpp"
#include "RandomEngine/API/Graphics/Shape.hpp"
#include "RandomEngine/API/System/Mouse.hpp"
#include "RandomEngine/API/GlobalData.hpp"
#include "RandomEngine/API/Application.hpp"

namespace random_engine
{
	void Button::updateComponentsAlignment()
	{
	}
	void Button::handleEvents(const sf::Event& e)
	{
		Rect hitbox{
			sprite.getPosition() - sprite.getScale() * 0.5f,
			sprite.getPosition() + sprite.getScale() * 0.5f
		};
		switch (e.type)
		{
		case sf::Event::MouseButtonPressed:
			if (Collision::areIntersected(Mouse::getPosition(*camera), hitbox)) {
				mouse_has_pressed = true;
				if (onPressed)
					onPressed(*this);
				throw AbortEventProcessing();
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (mouse_has_pressed and Collision::areIntersected(Mouse::getPosition(*camera), hitbox))
			{
				mouse_has_pressed = false;
				if (onReleased)
					onReleased(*this);
				throw AbortEventProcessing();
			}
			break;
		}
	}
	void Button::update(float delta)
	{
	}
	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
	}
}