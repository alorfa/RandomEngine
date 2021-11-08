#pragma once

#include <SFML/Window/Event.hpp>

namespace game
{
	class IGameObject
	{
	public:
		virtual void handleEvents(const sf::Event& e);
		virtual void update(float delta) = 0;
	};
}