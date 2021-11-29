#pragma once

#include <SFML/System/Vector2.hpp>
#include <stdint.h>

namespace random_engine 
{
	template <typename T>
	struct vector2 : public sf::Vector2<T>
	{
	public:
		vector2(T x = 0, T y = 0)
		{
			this->x = x;
			this->y = y;
		}
		template <typename U>
		vector2(const sf::Vector2<U>& v)
		{
			this->x = (T)v.x;
			this->y = (T)v.y;
		}

		template <typename U>
		vector2<U> as() const
		{
			return vector2<U>((U)this->x, (U)this->y);
		}

		T square_length() const
		{
			return this->x * this->x + this->y * this->y;
		}
		float length() const
		{
			return sqrtf(static_cast<float>(square_length()));
		}
		void normalize()
		{
			if (square_length() == 0)
				return;
			float rev_len = 1.f / length();
			this->x *= rev_len;
			this->y *= rev_len;
		}
		vector2<T> new_normalized() const
		{
			vector2<T> result = *this;
			result.normalize();
			return result;
		}
	};
	template <typename T>
	vector2<T> operator*(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
	{
		return vector2<T>(
			v1.x * v2.x,
			v1.y * v2.y
			);
	}

	template <typename T>
	vector2<T> operator/(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
	{
		return vector2<T>(
			v1.x / v2.x,
			v1.y / v2.y
			);
	}

	using fvec2 = vector2<float>;
	using vec2 = fvec2;
	using uvec2 = vector2<uint32_t>;
	using ivec2 = vector2<int32_t>;
}