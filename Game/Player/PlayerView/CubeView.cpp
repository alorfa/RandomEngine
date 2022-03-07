#include "CubeView.hpp"
#include <RandomEngine/API/Resource/TextureLoader.hpp>
#include <RandomEngine/API/GlobalData.hpp>
#include "Game/Player.hpp"
#include "IconUnits.hpp"
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include <RandomEngine/API/Auxiliary/print_vectors.hpp>

namespace
{
	float computeNeededRotation(const vec2& place_normal, float sprite_rotation)
	{
		constexpr float ROTATION = 0.7070707f;

		const vec2 player_look = Math::getCirclePoint(Math::rad(sprite_rotation + 90.f), { 1.f, 1.f });
		const float scalar = player_look ^ place_normal;
		//bottom
		if (Math::inRange(scalar, ROTATION, 1.f))
		{
			if (sprite_rotation > 180.f)
				return 360.f;
			return 0.f;
		}
		//top
		else if (Math::inRange(scalar, -1.f, -ROTATION))
		{
			return 180.f;
		}
		else
		{
			const vec2 player_look = Math::getCirclePoint(Math::rad(sprite_rotation), { 1.f, 1.f });
			const float scalar = player_look ^ place_normal;

			//left
			if (Math::inRange(scalar, ROTATION, 1.f))
			{
				return 90.f;
			}
			//right
			else
			{
				return 270.f;
			}
		}
	}
}

namespace game
{
	CubeView::CubeView(const sf::Color& main, const sf::Color& side, uint32 id, const Player& p)
		: PlayerView(Cube)
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
	void CubeView::update(float delta)
	{
		const auto& offsets = player->getContactOffsets();
		if (offsets.size() == 0)
		{
			sprite.rotate(-340.f * delta);
			return;
		}

		vec2 to_offset = offsets[0];
		to_offset.normalize();
		// TODO: compute needed offset
		for (const auto& offset : offsets)
		{

		}

		float rotation = sprite.getRotation();
		const float needed_rotation = computeNeededRotation(to_offset, rotation);
		sprite.setRotation(Math::linearSmooth(rotation, needed_rotation, 50.f, delta));
	}
	void CubeView::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		sprite.setPosition(player->getPosition());
		sprite.setScale(player->getScale());
		sprite.drawReverse(target, states);
	}
}