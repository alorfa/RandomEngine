#pragma once

#include <RandomEngine/API/Math/Vec2.hpp>
#include "CollisionArea.hpp"

using namespace random_engine;

namespace game
{
	class RectangleArea 
	{
	public:
		Vec2 position;
		Vec2 size;
		float rotation;

		RectangleArea(const Vec2& pos, const Vec2& size, float rotation);

		bool touches(const Player&) const ;
		RepulsionResult getRepulsionVector(const Player&) const;
	};
}