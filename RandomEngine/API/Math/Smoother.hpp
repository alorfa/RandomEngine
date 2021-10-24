#pragma once

#include "RandomEngine/API/Math/vec2.hpp"

namespace random_engine
{
	class Smoother
	{
	public:
		static vec2 linear(const vec2& cur_pos, const vec2& end_pos, float speed, float delta);
	};
}