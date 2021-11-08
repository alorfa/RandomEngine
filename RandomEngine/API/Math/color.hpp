#pragma once

#include "RandomEngine/API/System/types.hpp"
#include <SFML/Graphics/Color.hpp>

namespace random_engine
{
	struct color3f
	{
		float01 r, g, b;
		sf::Color toSfColor() const;
	};
	struct color4f
	{
		float01 r, g, b, a;
		sf::Color toSfColor() const;
	};
}