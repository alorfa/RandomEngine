#pragma once

#include <RandomEngine/API/Math/vec2.hpp>
#include <iostream>

namespace random_engine
{
	template <typename T>
	std::ostream& operator<<(std::ostream& stream, const sf::Vector2<T>& v)
	{
		stream << "[" << v.x << ", " << v.y << ']';
		return stream;
	}
}