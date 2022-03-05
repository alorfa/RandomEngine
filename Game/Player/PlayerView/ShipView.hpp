#pragma once

#include "Game/Player/PlayerView.hpp"
#include <RandomEngine/API/Graphics/MultiSprite.hpp>

namespace game
{
	class ShipView : public PlayerView
	{
		mutable sf::Transformable transform;
		MultiSprite ship, cube;
		const Player* player = nullptr;
	public:
		ShipView(const sf::Color& main, const sf::Color& side, 
			uint32 ship_id, uint32 cube_id, const Player& p);

		void setMainColor(const sf::Color& color);
		void setSideColor(const sf::Color& color);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}