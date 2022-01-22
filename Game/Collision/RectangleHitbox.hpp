#pragma once

#include <RandomEngine/API/Math/vec2.hpp>
#include "Hitbox.hpp"

using namespace random_engine;

namespace game
{
	class RectangleHitbox
	{
	public:
		vec2 position;
		vec2 size;
		float rotation;

		mutable PhysicalRotateableRect rect;

		RectangleHitbox(const vec2& pos, const vec2& size, float rotation);

		bool touches(const Hitbox&) const;
		RepulsionResult getRepulsionVector(const Hitbox&) const;
	};
}