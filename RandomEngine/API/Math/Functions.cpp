#include "Functions.hpp"
#include <corecrt_math_defines.h>
#include <cmath>

namespace random_engine
{
	constexpr float RAD2DEG = float(180./M_PI);
	constexpr float DEG2RAD = float(M_PI/180.);

	float Math::sin(float angle)
	{
		return sinf(angle);
	}
	float Math::cos(float angle)
	{
		return cosf(angle);
	}
	float Math::rad(float deg) {
		return deg * DEG2RAD;
	}
	float Math::deg(float rad) {
		return rad * RAD2DEG;
	}
	Vec2 Math::getCirclePoint(float rad, const Vec2& size)
	{
		Vec2 result;
		result.x = cos(rad) * size.x;
		result.y = sin(rad) * size.y;
		return result;
	}
	Vec2 Math::linearSmooth(const Vec2& cur_pos, const Vec2& end_pos, float speed, float delta)
	{
		float offset = speed * delta;
		offset = clamp(offset, 0.f, 1.f);
		return linearInterpolate(cur_pos, end_pos, offset);
	}
}