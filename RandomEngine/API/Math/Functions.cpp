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
	vec2 Math::getCirclePoint(float rad, const vec2& size)
	{
		vec2 result;
		result.x = cos(rad) * size.x;
		result.y = sin(rad) * size.y;
		return result;
	}
	float Math::getAngle(const vec2& vector)
	{
		const float asine = asinf(vector.y);
		const float acosine = acosf(vector.x);

		if (asine >= 0.f)
			return acosine;
		//return acosine - (PI - acosine);
		return TAU - acosine;
	}
}