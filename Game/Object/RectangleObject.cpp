#include "RectangleObject.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace game
{
	void RectangleObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite);
	}
}