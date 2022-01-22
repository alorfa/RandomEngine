#pragma once

#include "RepulsionResult.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace random_engine
{
	class Application;

	struct Rect
	{
		// left bottom point
		vec2 min;
		// right top point
		vec2 max;

		inline Rect(const vec2& min = {}, const vec2& max = {})
			: min(min), max(max) {}
	};
	struct PhysicalRect : Rect
	{
		vec2 center;
		// pos - prev_pos
		vec2 movement;
		vec2 direction;
	};
	struct PhysicalRotateableRect : PhysicalRect
	{
		float rotation = 0.f;
	};

	struct Line
	{
		vec2 begin;
		vec2 direction;

		inline Line(const vec2& begin = {}, const vec2& direction = {})
			: begin(begin), direction(direction) {}
	};

	struct ContactLineRect
	{
		vec2 normal;
		vec2 point;
		float t_hit_near = 0;
		bool touches = false;
	};

	class Collision
	{
		friend class Application;

		inline static sf::RenderWindow* window = nullptr;
	public:
		static bool areIntersected(const vec2& point, const Rect& rect);
		static bool areIntersected(const Rect& rect1, const Rect& rect2);
		static bool areIntersected(const Line& l1, const Line& l2);

		static ContactLineRect contact(const Line& line, const Rect& rect);

		static RepulsionResult collide(const PhysicalRect& rect1, const PhysicalRect& rect2);
	};
}