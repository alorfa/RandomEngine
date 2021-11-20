#pragma once
#include "RepulsionResult.hpp"

namespace random_engine
{
	struct AxisAlignedBox
	{
		Vec2 min;
		Vec2 max;

		static AxisAlignedBox fromPoint(Vec2 const& point)
		{
			return { point, point };
		}

		void update(Vec2 const& point)
		{
			if(min.x > point.x)
				min.x = point.x;
			else if(max.x < point.x)
				max.x = point.x;
			if(min.y > point.y)
				min.y = point.y;
			else if(max.y < point.y)
				max.y = point.y;
		}

		static AxisAlignedBox fromCenterScale(Vec2 const& cen, Vec2 const& scale = {})
		{
			return { cen - scale, cen + scale };
		}
	};

	struct Disk
	{
		Vec2 center;
		float radius;

		AxisAlignedBox aabb() const {
			return { {center.x - radius, center.y - radius},
				   {center.x + radius, center.y + radius} };
		}
	};

	struct Segment
	{
		Vec2 start;
		Vec2 end;

		AxisAlignedBox aabb() const {
			auto box = AxisAlignedBox::fromPoint(start);
			box.update(end);
			return box;
		}
	};

	struct Line
	{
		Vec2 start;
		Vec2 dir;

		AxisAlignedBox aabb() const // for consistency
		{
			constexpr float n_inf = std::numeric_limits<float>::min();
			constexpr float p_inf = std::numeric_limits<float>::max();
			return {{n_inf, n_inf}, {p_inf, p_inf}};
		}
	};

	struct Ray
	{
		Vec2 start;
		Vec2 dir;

		AxisAlignedBox aabb() const // for consistency
		{
			auto box = AxisAlignedBox::fromPoint(start);
			float constexpr bigVal = 1.e10;
			box.update(start + bigVal * dir); // 
			return box;
		}
	};

	template<int N>
	struct PolyLine
	{
		static_assert(N > 2);
		Vec2 points[N];

		AxisAlignedBox aabb() const
		{
			auto box = AxisAlignedBox::fromPoint(points[0]);
			for(int k = 1; k < N; ++k)
				box.update(points[k]);
			return box;
		}
	};

	class Collision
	{
	public:
		static bool areIntersected(const AxisAlignedBox& box1, const AxisAlignedBox& box2);
		static bool areIntersected(const Disk& disc1, const Disk& disc2);
		static bool areIntersected(const Segment& segment1, const Segment& segment2);

		// cross implementations
		static bool areIntersected(const AxisAlignedBox& box, const Disk& disc);
		static bool areIntersected(const Disk& disk, const Segment& segment);


		// cross symmetric implementations
		static inline bool areIntersected(const Disk& disc, const AxisAlignedBox& box) { return areIntersected(box, disc); }
		static inline bool areIntersected(const Segment& segment, const Disk& disk) { return areIntersected(disk, segment); }
	};
}