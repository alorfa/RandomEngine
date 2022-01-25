#pragma once

#include "RandomEngine/API/Graphics/Sprite.hpp"

namespace random_engine
{
	class Camera;
	class Scene;

	class UIComponent : public Sprite
	{
	public:
		const Camera* camera = nullptr;
		Scene* owner = nullptr;

		virtual void handleEvents(const sf::Event& e) = 0;
		virtual void update(float delta) = 0;
	};
}