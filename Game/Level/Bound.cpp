#include "Bound.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "Game/Player.hpp"
#include <iostream>
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>

using namespace random_engine;

namespace game
{
	Bound::Bound(Location location, const Camera& camera)
		: location(location), camera(&camera)
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
		const int outX = (int)camera->getPosition().x / SEGMENT_SIZE;
		sprite.setPosition(float(outX * SEGMENT_SIZE), posY);
		
		sprite.setScale(48.f, 4.f);

		target.draw(sprite);
	}
	bool Bound::touches(const Player& player) const
	{		
		if (location == Bound::Bottom)
		{
			//player y more then ground y, and the size of the cube is also taken into account
			if (posY > player.getPosition().y - player.getScale().y * 0.5f)
				return true;
		}
		if (location == Bound::Top)
		{
			if (posY < player.getPosition().y + player.getScale().y * 0.5f)
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
			const float offset = posY - (player.getPosition().y - player.getScale().y * 0.5f);
			if (offset > 0.f)
			{
				result.offset = { 0.f, offset };
				result.touches = true;
			}
			return result;
		}
		if (location == Bound::Top)
		{
			const float offset = posY - (player.getPosition().y + player.getScale().y * 0.5f);
			if (offset < 0.f)
			{
				result.offset = { 0.f, offset };
				result.touches = true;
			}
		}
		return result;
	}
}