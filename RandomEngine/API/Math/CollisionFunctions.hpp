#pragma once

#include "RepulsionResult.hpp"

namespace random_engine
{
	struct Rect
	{
		// left bottom point
		vec2 p1;
		// right top point
		vec2 p2;

		inline Rect(const vec2& p1 = {}, const vec2& p2 = {})
			: p1(p1), p2(p2) {}
	};


	class Collision
	{
	public:
		static bool RectTouchesRect(const Rect& rect1, const Rect& rect2);
	};
}