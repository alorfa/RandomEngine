#include "BallView.hpp"
#include <RandomEngine/API/Resource/TextureLoader.hpp>
#include <RandomEngine/API/GlobalData.hpp>
#include <RandomEngine/API/Math/CollisionFunctions.hpp>
#include "IconUnits.hpp"
#include "Game/Player.hpp"

namespace game
{
	BallView::BallView(const sf::Color& main, const sf::Color& side, uint32 id, const Player& p)
		: PlayerView(Ball)
	{
		sprite.setCount(2);
		sprite[0].texture = sprite[1].texture = &textureLoader.load(res / "img/icons.png");

		setMainColor(main);
		setSideColor(side);

		const Rect area{
			{ float(id * 2) * X_UNIT, 1.f - Y_UNIT * 3.f },
			{ float(id * 2 + 1) * X_UNIT, 1.f - Y_UNIT * 2.f }
		};
		sprite[0].setArea(area.min, area.max);
		sprite[1].setArea(area.min + vec2{ X_UNIT }, area.max + vec2{ X_UNIT });

		player = &p;
	}
	void BallView::setMainColor(const sf::Color& color)
	{
		sprite[0].setColor(color);
	}
	void BallView::setSideColor(const sf::Color& color)
	{
		sprite[1].setColor(color);
	}
	void BallView::update(float delta)
	{
		sprite.rotate(player->direction.x * (float)Math::sign(player->game_mode.gravity)
			* 36.f * delta);
	}
	void BallView::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		sprite.setPosition(player->getPosition());
		sprite.setScale(player->getScale());
		sprite.drawReverse(target, states);
	}
}