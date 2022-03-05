#include "CubeView.hpp"
#include <RandomEngine/API/Resource/TextureLoader.hpp>
#include <RandomEngine/API/GlobalData.hpp>
#include "Game/Player.hpp"
#include "IconUnits.hpp"

namespace game
{
	CubeView::CubeView(const sf::Color& main, const sf::Color& side, uint32 id, const Player& p)
	{
		sprite.setCount(2);
		sprite[0].texture = sprite[1].texture = &textureLoader.load(res / "img/icons.png");

		setMainColor(main);
		setSideColor(side);

		const Rect area{
			{ float(id * 2) * X_UNIT, 1.f - Y_UNIT },
			{ float(id * 2 + 1) * X_UNIT, 1.f }
		};
		sprite[0].setArea(area.min, area.max);
		sprite[1].setArea(area.min + vec2{ X_UNIT }, area.max + vec2{ X_UNIT });

		player = &p;
	}
	void CubeView::setMainColor(const sf::Color& color)
	{
		sprite[0].setColor(color);
	}
	void CubeView::setSideColor(const sf::Color& color)
	{
		sprite[1].setColor(color);
	}
	void CubeView::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		sprite.setPosition(player->getPosition());
		sprite.setScale(player->getScale());
		sprite.drawReverse(target, states);
	}
}