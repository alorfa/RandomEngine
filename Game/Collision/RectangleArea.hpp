#pragma once

#include <RandomEngine/API/Math/vec2.hpp>
#include "CollisionArea.hpp"

using namespace random_engine;

namespace game
{
	class RectangleArea 
	{
	public:
		vec2 position;
		vec2 size;
		float rotation;

		RectangleArea(const vec2& pos, const vec2& size, float rotation);

		bool touches(const Player&) const ;
		StaticBody::RepulsionResult getRepulsionVector(const Player&) const;
	};
}