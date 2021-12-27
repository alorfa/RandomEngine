#include "CollisionFunctions.hpp"
#include <cmath>
#include <algorithm>
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include <RandomEngine/API/Auxiliary/print_vectors.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <RandomEngine/API/Graphics/VertexObject.hpp>
#include <RandomEngine/API/Graphics/Sprite.hpp>

namespace random_engine
{
	bool Collision::areIntersected(const Rect& cube, const Rect& rect)
	{
		return (
			cube.max.x > rect.min.x &&
			cube.min.x < rect.max.x &&
			cube.max.y > rect.min.y &&
			cube.min.y < rect.max.y);
	}

	bool Collision::areIntersected(const Line& l1, const Line& l2)
	{
		const float temp = (l2.direction.y * l1.direction.x) - (l2.direction.x * l1.direction.y);

		const float uA = (l2.direction.x * (l1.begin.y - l2.begin.y) -
			(l2.direction.y * (l1.begin.x - l2.begin.x))) / temp;
		const float uB = (l1.direction.x * (l1.begin.y - l2.begin.y) -
			(l1.direction.y * (l1.begin.x - l2.begin.x))) / temp;

		return (uA >= 0 && uA <= 1) and (uB >= 0 && uB <= 1);
	}

	ContactLineRect Collision::contact(const Line& line, const Rect& rect)
	{
		constexpr float eps = 1.e-10f;
		ContactLineRect result;

		// Cache division
		vec2 invdir = vec2{ 1.f, 1.f } / line.direction;

		// Calculate intersections with rectangle bounding axes
		vec2 t_near = (rect.min - line.begin) * invdir;
		vec2 t_far = (rect.max - line.begin) * invdir;

		if (std::isnan(t_far.y) or std::isnan(t_far.x))
			return result;
		if (std::isnan(t_near.y) or std::isnan(t_near.x)) 
			return result;

		// Sort distances
		if (t_near.x > t_far.x) 
			std::swap(t_near.x, t_far.x);
		if (t_near.y > t_far.y)
			std::swap(t_near.y, t_far.y);

		// Early rejection		
		if (t_near.x > t_far.y || t_near.y > t_far.x) return result;

		// Closest 'time' will be the first contact
		result.t_hit_near = std::max(t_near.x, t_near.y);

		// Furthest 'time' is contact on opposite side of target
		float t_hit_far = std::min(t_far.x, t_far.y);

		// Reject if ray direction is pointing away from object
		if (t_hit_far < eps)
			return result;

		// Contact point of collision from parametric line equation
		result.point = line.begin + result.t_hit_near * line.direction;

		if (t_near.x > t_near.y)
			if (invdir.x < 0)
				result.normal = { 1, 0 };
			else
				result.normal = { -1, 0 };
		else if (t_near.x < t_near.y)
			if (invdir.y < 0)
				result.normal = { 0, 1 };
			else
				result.normal = { 0, -1 };

		// Note if t_near == t_far, collision is principly in a diagonal
		// so pointless to resolve. By returning a CN={0,0} even though its
		// considered a hit, the resolver wont change anything.
		result.touches = (result.t_hit_near < 1.0f - eps);
		return result;
	}

	RepulsionResult Collision::collide(const PhysicalRect& cube, const PhysicalRect& rect)
	{
		RepulsionResult result;

		Line line;
		line.begin = cube.center;
		line.direction = cube.movement - rect.movement;
        line.begin -= line.direction; // we need previous position
        if(line.direction.square_length() < 1.e-2 && !Collision::areIntersected(cube, rect))
            return result;


        Rect collision_rect;
        const vec2 cube_size = cube.max - cube.min;
		collision_rect.min = rect.min - cube_size * 0.5f;
		collision_rect.max = rect.max + cube_size * 0.5f;

		const auto [normal, touch_point, contact_time, touches] = Collision::contact(line, collision_rect);
        if(!touches)
            return result;

		result.touches = touches;
		result.direction = rect.direction;
		result.normal = normal;

		if (normal.x > 0)
		{
			result.offset.x = rect.max.x - cube.min.x;
		}
		if (normal.x < 0)
		{
			result.offset.x = rect.min.x - cube.max.x;
		}
		if (normal.y > 0)
		{
			result.offset.y = rect.max.y - cube.min.y;
		}
		if (normal.y < 0)
		{
			result.offset.y = rect.min.y - cube.max.y;
		}
		
		return result;
	}

}