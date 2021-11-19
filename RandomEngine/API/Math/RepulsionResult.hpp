#pragma once

#include "RandomEngine/API/Math/vec2.hpp"

namespace random_engine
{
	struct RepulsionResult
	{
		bool touches = false;
		vec2 offset;
		vec2 direction;
	};
}