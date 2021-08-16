#pragma once

#include <cmath>
#include <RandomEngine/API/Math/vec2.hpp>

namespace random_engine
{
	class Trig
	{
	public:
		static constexpr float PI = 3.1415926535f;
		static constexpr float TAU = 2.f * PI;

		static inline float sin(float angle) {
			return sinf(angle);
		}
		static inline float cos(float angle) {
			return cosf(angle);
		}
		static inline float rad(float deg) {
			return deg / 180.f * PI;
		}
		static inline float deg(float rad) {
			return rad * 180.f / PI;
		}
		static vec2 getCirclePoint(float rad, const vec2& size);
	};
}