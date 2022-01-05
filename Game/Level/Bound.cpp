#include "Bound.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "Game/Player.hpp"
#include <iostream>
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include <RandomEngine/API/GlobalData.hpp>

using namespace random_engine;

namespace game
{
	Bound::Bound(Location location)
		: location(location)
	{
		if (location == Bound::Top) {
			sprite.setArea({ 0.f, 1.f }, { 12.f, 0.f });
			sprite.setOrigin(0.f, -0.5f);
		}
		else {
			sprite.setArea({ 0.f, 0.f }, { 12.f, 1.f });
			sprite.setOrigin(0.f, 0.5f);
		}
		
	}
	void Bound::setTexture(const Texture& t)
	{
		sprite.setTexture(t);
	}
	void Bound::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		auto& global_data = GlobalData::getInstance();
		const vec2 size = global_data.camera.getNativeSize();
		const vec2& cam_pos = global_data.camera.getPosition();
		vec2 min = { cam_pos.x*0.25f - size.x*0.125f, 0.f };
		vec2 max = { cam_pos.x*0.25f + size.x*0.125f, 1.f };
		if (location == Bound::Top)
		{
			min.y = 1.f;
			max.y = 0.f;
		}
		sprite.setPosition(cam_pos.x, pos.y);
		
		sprite.setScale(size.x, 4.f);
		sprite.setArea(min, max);

		target.draw(sprite);
	}
	bool Bound::touches(const Player& player) const
	{		
		if (location == Bound::Bottom)
		{
			//player y more then ground y, and the size of the cube is also taken into account
			if (pos.y > player.getPosition().y - player.getScale().y * 0.5f)
				return true;
		}
		if (location == Bound::Top)
		{
			if (pos.y < player.getPosition().y + player.getScale().y * 0.5f)
				return true;
		}
		return false;
	}
	RepulsionResult Bound::getRepulsionVector(const Player& player) const
	{
		RepulsionResult result;
		if (location == Bound::Bottom)
		{
			//player y more then ground y, and the size of the cube is also taken into account
			const float offset = pos.y - (player.getPosition().y - player.getScale().y * 0.5f);
			if (offset > 0.f)
			{
				result.offset = { 0.f, offset };
				result.touches = true;
			}
			return result;
		}
		if (location == Bound::Top)
		{
			const float offset = pos.y - (player.getPosition().y + player.getScale().y * 0.5f);
			if (offset < 0.f)
			{
				result.offset = { 0.f, offset };
				result.touches = true;
			}
		}
		return result;
	}
}