#include "color.hpp"

namespace random_engine
{
	sf::Color color3f::toSfColor() const
	{
		return sf::Color(
			r * 255.f,
			g * 255.f,
			b * 255.f);
	}
	sf::Color color4f::toSfColor() const
	{
		return sf::Color(
			r * 255.f,
			g * 255.f,
			b * 255.f,
			a * 255.f);
	}
}