#pragma once

#include <SFML/System/Vector2.hpp>
#include <stdint.h>

namespace random_engine 
{
	template <typename T>
	struct al_vec : public sf::Vector2<T>
	{
	public:
		al_vec(T x = 0, T y = 0)
		{
			this->x = x;
			this->y = y;
		}
		template <typename U>
		al_vec(const sf::Vector2<U>& v)
		{
			this->x = (T)v.x;
			this->y = (T)v.y;
		}

		template <typename U>
		al_vec<U> as() const
		{
			return al_vec<U>((U)this->x, (U)this->y);
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
		al_vec<T> new_normalized() const
		{
			al_vec<T> result = *this;
			result.normalize();
			return result;
		}
	};
	template <typename T>
	al_vec<T> operator*(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
	{
		return al_vec<T>(
			v1.x * v2.x,
			v1.y * v2.y
			);
	}

	template <typename T>
	al_vec<T> operator/(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
	{
		return al_vec<T>(
			v1.x / v2.x,
			v1.y / v2.y
			);
	}

	using fvec2 = al_vec<float>;
	using vec2 = fvec2;
	using uvec2 = al_vec<uint32_t>;
	using ivec2 = al_vec<int32_t>;
}