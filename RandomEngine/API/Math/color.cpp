#include "color.hpp"

namespace random_engine
{
	sf::Color color3f::toSfColor() const
	{
		return sf::Color(
			uint8(r * 255.f),
			uint8(g * 255.f),
			uint8(b * 255.f));
	}
	sf::Color color4f::toSfColor() const
	{
		return sf::Color(
			uint8(r * 255.f),
			uint8(g * 255.f),
			uint8(b * 255.f),
			uint8(a * 255.f));
	}
}