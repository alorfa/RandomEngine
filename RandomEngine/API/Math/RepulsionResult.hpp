#pragma once

#include "RandomEngine/API/Math/Vec2.hpp"

namespace random_engine
{
	struct RepulsionResult
	{
		bool touches = false;
		Vec2 offset;
		Vec2 direction;
	};
}