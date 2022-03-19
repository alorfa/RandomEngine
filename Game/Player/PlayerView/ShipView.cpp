#include "ShipView.hpp"
#include <RandomEngine/API/Resource/TextureLoader.hpp>
#include <RandomEngine/API/GlobalData.hpp>
#include <RandomEngine/API/Math/CollisionFunctions.hpp>
#include "IconUnits.hpp"
#include "Game/Player.hpp"
#include "RandomEngine/API/Auxiliary/DEBUG.hpp"

namespace game
{
	ShipView::ShipView(const sf::Color& main, const sf::Color& side, 
		uint32 ship_id, uint32 cube_id, const Player& p)
		: PlayerView(Ship)
	{
		ship.setCount(2);
		cube.setCount(2);
		cube[0].texture = cube[1].texture = ship[0].texture = ship[1].texture =
			&textureLoader.load(res / "img/icons.png");

		setMainColor(main);
		setSideColor(side);

		const Rect cube_area{
			{ float(cube_id * 2) * X_UNIT, 1.f - Y_UNIT },
			{ float(cube_id * 2 + 1) * X_UNIT, 1.f }
		};
		cube[0].setArea(cube_area.min, cube_area.max);
		cube[1].setArea(cube_area.min + vec2{ X_UNIT }, cube_area.max + vec2{ X_UNIT });
		const Rect ship_area{
			{ float(ship_id * 2) * X_UNIT, 1.f - 2.f * Y_UNIT },
			{ float(ship_id * 2 + 1) * X_UNIT, 1.f - Y_UNIT }
		};
		ship[0].setArea(ship_area.min, ship_area.max);
		ship[1].setArea(ship_area.min + vec2{ X_UNIT }, ship_area.max + vec2{ X_UNIT });

		cube.setScale(0.5f, 0.5f);
		cube.setPosition(0.f, 0.2f);

		player = &p;
	}
	void ShipView::setMainColor(const sf::Color& color)
	{
		ship[0].setColor(color);
		cube[0].setColor(color);
	}
	void ShipView::setSideColor(const sf::Color& color)
	{
		ship[1].setColor(color);
		cube[1].setColor(color);
	}
	void ShipView::update(float delta)
	{
		rotation = Math::linearSmooth(rotation, player->direction.y * 2.f, 20.f, delta);
		transform.setRotation(rotation);
	}
	void ShipView::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		transform.setPosition(player->getPosition());
		if (Math::sign(player->game_mode.gravity) == -1)
			transform.setScale(player->getScale());
		else
			transform.setScale(player->getScale() * vec2(1.f, -1.f));
		states.transform *= transform.getTransform();
		cube.drawReverse(target, states);
		ship.drawReverse(target, states);
	}
}