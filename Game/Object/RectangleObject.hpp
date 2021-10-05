#pragma once

#include <Game/Object.hpp>
#include <RandomEngine/API/Graphics/Sprite.hpp>

namespace game
{
	class RectangleObject : public Object
	{
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		random_engine::Sprite sprite;

	};
}