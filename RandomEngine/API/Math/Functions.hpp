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
		static T sign(T value)
		{
			if (value > static_cast<T>(0))
				return static_cast<T>(1);
			if (value < static_cast<T>(0))
				return static_cast<T>(-1);
			return static_cast<T>(0);
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
		static T linearInterpolate(const T& a, const T& b, float t)
		{
			return a + (b - a) * t;
		}
		static vec2 linearSmooth(const vec2& cur_pos, const vec2& end_pos, float speed, float delta);
	};
}