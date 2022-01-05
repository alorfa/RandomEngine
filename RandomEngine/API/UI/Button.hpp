#pragma once

#include <SFML/Window/Event.hpp>
#include "RandomEngine/API/Graphics/Sprite.hpp"
#include "RandomEngine/API/Math/CollisionFunctions.hpp"

namespace random_engine
{
	class Button : public Sprite
	{
		bool mouse_has_pressed = false;
	public:
		using Event = void (*)();

		Event onClick = nullptr;

		void handleEvents(const sf::Event& e);
	};
}