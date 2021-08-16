#include <RandomEngine/API/Math.hpp>

namespace random_engine
{
	vec2 Trig::getCirclePoint(float rad, const vec2& size)
	{
		vec2 result;
		result.x = Trig::cos(rad) * size.x;
		result.y = Trig::sin(rad) * size.y;
		return result;
	}
}