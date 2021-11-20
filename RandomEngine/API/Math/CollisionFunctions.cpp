#include "CollisionFunctions.hpp"

namespace random_engine
{
	inline float squared(float x) { return x * x; }

	bool Collision::areIntersected(const AxisAlignedBox& box1, const AxisAlignedBox& box2)
	{
		return
			box1.max.x >= box2.min.x &&
			box1.min.x <= box2.max.x &&
			box1.max.y >= box2.min.y &&
			box1.min.y <= box2.max.y;
	}

	bool Collision::areIntersected(const AxisAlignedBox& box, const Disk& disc)
	{
		if(box.max.x >= disc.center.x - disc.radius &&
		   box.min.x <= disc.center.x + disc.radius &&
		   box.max.y >= disc.center.y - disc.radius &&
		   box.min.y <= disc.center.y - disc.radius)
		{
			auto const square_radius = disc.radius * disc.radius;
			return (box.min - disc.center).square_length() < square_radius ||
				(box.max - disc.center).square_length() < square_radius ||
				(Vec2{ box.min.x, box.max.y } - disc.center).square_length() < square_radius ||
				(Vec2{ box.max.x, box.min.y } - disc.center).square_length() < square_radius;
		}
		else
			return false;
	}

	bool Collision::areIntersected(const Disk& disc1, const Disk& disc2)
	{
		return (disc1.center - disc2.center).square_length() <= squared(disc1.radius + disc2.radius);
	}


	bool Collision::areIntersected(const Disk& disk, const Segment& segment)
	{
		Vec2 const dir = segment.end - segment.start;
		Vec2 const cen = disk.center - segment.start;
		// solving equation norm(dir*t-cen) = R^2
		// norm(dir)^2 * t^2 - 2*(dir|cen)*t+norm(cen)^2-R^2 = 0
		// D/4 = (dir|cen)^2 - norm(dir)^2*(norm(cen)^2-R^2)
		double const dir2 = dir.square_length();
		double const cen2 = cen.square_length();
		double const dircen = (dir | cen);
		double const R2 = squared(disk.radius);
		double const tmin = dircen / dir2;
		double const D = dircen * tmin - (cen2 - R2);
		if(D < 0) // not intersection
			return false;
		if(0 <= tmin && tmin < 1) // closest point is in interval [0;1] <-> [start;end] => intersection
			return true;
		return cen2 <= R2 || (cen - dir).square_length() <= R2; // one of edge points is within disc
	}


	bool Collision::areIntersected(const Segment& segment1, const Segment& segment2)
	{
		Vec2 const dir1 = segment1.end - segment1.start;
		Vec2 const dir2 = segment2.start - segment2.end;
		Vec2 const y = segment2.start - segment1.start;
		double const det = dir1 ^ dir2;
		constexpr double eps = 1.e-5;
		if(fabs(det) < eps) // almost parallel lines
			return y.sumAbs() < eps; // very small distance so may be matched
		double const t1 = (y ^ dir2) / det; // Cramer's rule
		double const t2 = (dir1 ^ y) / det;
		return 0 <= t1 && t1 <= 1 
			&& 0 <= t2 && t2 <= 1;
	}

}