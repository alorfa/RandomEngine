#pragma once

#include "RandomEngine/API/Math/vec2.hpp"

namespace random_engine
{
	struct RepulsionResult
	{
		// how much the object will be pushed away 
		vec2 offset;
		// the direction that the object will have after collision 
		vec2 direction;
		// the normal of the surface
		vec2 normal;
		bool touches = false;
	};
}