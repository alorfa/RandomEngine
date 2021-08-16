#pragma once

namespace random_engine
{
	class Interpolation
	{
	public:
		template <typename T>
		static T linear(const T& a, const T& b, float t)
		{
			return a + (b - a) * t;
		}
	};
}