#pragma once

#include <SFML/Window/Event.hpp>
#include "RandomEngine/API/Graphics/Sprite.hpp"
#include "RandomEngine/API/Math/CollisionFunctions.hpp"
#include "RandomEngine/API/Graphics/Camera.hpp"
#include "RandomEngine/API/Scene.hpp"

namespace random_engine
{
	class Button : public Sprite
	{
		bool mouse_has_pressed = false;
	public:
		using Event = void (*)(Scene& scene);
		const Camera* camera = nullptr;
		Scene* scene = nullptr;

		Event onClick = nullptr;

		void handleEvents(const sf::Event& e);
	};
}