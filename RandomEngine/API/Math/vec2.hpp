#pragma once

#include <SFML/System/Vector2.hpp>
#include <stdint.h>

namespace random_engine 
{
	template <typename T>
	struct AlgebraicVec2 : public sf::Vector2<T>
	{
	public:
		using sf::Vector2<T>::Vector2;

		template<typename U>
		AlgebraicVec2(sf::Vector2<U> const& u): sf::Vector2<T>{u} {}

		AlgebraicVec2(AlgebraicVec2&&) = default;
        AlgebraicVec2(AlgebraicVec2 const&) = default;

        AlgebraicVec2& operator=(AlgebraicVec2&&) = default;
        AlgebraicVec2& operator=(AlgebraicVec2 const&) = default;

		template <typename U>
		AlgebraicVec2<U> as() const
		{
			return AlgebraicVec2<U>(*this);
		}

		AlgebraicVec2 operator-(AlgebraicVec2 const& t) const { return (sf::Vector2<T> const&)(*this) - (sf::Vector2<T> const&)(t); }

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
			float inv_len = 1.f / length();
			this->x *= inv_len;
			this->y *= inv_len;
		}

		AlgebraicVec2<T> new_normalized() const
		{
			AlgebraicVec2<T> result = *this;
			result.normalize();
			return result;
		}
	};

	template <typename T>
	AlgebraicVec2<T> operator*(const AlgebraicVec2<T>& v1, const AlgebraicVec2<T>& v2)
	{
		return AlgebraicVec2<T>(
			v1.x * v2.x,
			v1.y * v2.y
			);
	}

	//dot product
    template <typename T>
    T operator|(const AlgebraicVec2<T>& v1, const AlgebraicVec2<T>& v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

	//cross-product
    template <typename T>
    T operator^(const AlgebraicVec2<T>& v1, const AlgebraicVec2<T>& v2)
    {
        return v1.x * v2.y - v1.y * v2.x;
    }

	template <typename T>
	AlgebraicVec2<T> operator/(const AlgebraicVec2<T>& v1, const AlgebraicVec2<T>& v2)
	{
		return AlgebraicVec2<T>(
			v1.x / v2.x,
			v1.y / v2.y
			);
	}

	using Vec2f = AlgebraicVec2<float>;
	using Vec2 = Vec2f;
	using Vec2u = AlgebraicVec2<uint32_t>;
	using Vec2i = AlgebraicVec2<int32_t>;
}