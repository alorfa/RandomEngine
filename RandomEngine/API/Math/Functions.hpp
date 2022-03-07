#pragma once

#include "RandomEngine/API/Math/vec2.hpp"

namespace random_engine
{
	class Math
	{
	public:
		static constexpr float PI = 3.1415926535f;
		static constexpr float TAU = 2.f * PI;

		static float sin(float angle);
		static float cos(float angle);
		static float rad(float deg);
		static float deg(float rad);
		static vec2 getCirclePoint(float rad, const vec2& size);

		template <typename T>
		static int sign(T value)
		{
			if (value > static_cast<T>(0))
				return 1;
			if (value < static_cast<T>(0))
				return -1;
			return 0;
		}
		template <typename T>
		static T clamp(T value, T min, T max)
		{
			if (value > max)
				return max;
			if (value < min)
				return min;
			return value;
		}
		template <typename T>
		static bool inRange(T value, T min, T max)
		{
			return (min <= value and value <= max);
		}
		template <typename T>
		static T linearInterpolate(const T& a, const T& b, float t)
		{
			return a + (b - a) * t;
		}
		template <typename T>
		static T linearSmooth(const T& cur_pos, const T& end_pos, float speed, float delta)
		{
			const float offset = clamp(speed * delta, 0.f, 1.f);
			return linearInterpolate(cur_pos, end_pos, offset);
		}
	};
}