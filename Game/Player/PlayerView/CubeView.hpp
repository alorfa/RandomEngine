#pragma once

#include "Game/Player/PlayerView.hpp"
#include <RandomEngine/API/Graphics/MultiSprite.hpp>

namespace game
{
	class CubeView : public PlayerView
	{
		mutable MultiSprite sprite;
		const Player* player = nullptr;
	public:
		CubeView(const sf::Color& main, const sf::Color& side, uint32 id, const Player& p);

		void setMainColor(const sf::Color& color);
		void setSideColor(const sf::Color& color);

		void update(float delta) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}