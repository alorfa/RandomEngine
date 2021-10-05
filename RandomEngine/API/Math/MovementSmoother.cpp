#include "MovementSmoother.hpp"

#include "RandomEngine/API/Math/Interpolation.hpp"

namespace
{
	template <typename T>
	T clamp(T value, T min, T max)
	{
		if (value > max)
			return max;
		if (value < min)
			return min;
		return value;
	}
}

namespace random_engine
{
	vec2 MovementSmoother::linear(const vec2& cur_pos, const vec2& end_pos, float speed, float delta)
	{
		float offset = speed * delta;
		offset = clamp(offset, 0.f, 1.f);
		return Interpolation::linear(cur_pos, end_pos, offset);
	}
}