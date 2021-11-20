#include "Functions.hpp"
#include <cmath>

namespace random_engine
{
	float Math::sin(float angle)
	{
		return sinf(angle);
	}
	float Math::cos(float angle)
	{
		return cosf(angle);
	}
	float Math::rad(float deg) {
		return deg / 180.f * PI;
	}
	float Math::deg(float rad) {
		return rad * 180.f / PI;
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