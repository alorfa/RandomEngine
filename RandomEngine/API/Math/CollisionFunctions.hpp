#pragma once
#include "RepulsionResult.hpp"

namespace random_engine
{
    struct AxisAlignedBox
    {
        Vec2 min;
        Vec2 max;

        static AxisAlignedBox fromCenterScale(Vec2 const& cen, Vec2 const& scale = {})
        {
            return {cen - scale, cen + scale};
        }
    };

    struct Disk
    {
        Vec2 center;
        float radius;
    };

    struct Segment
    {
        Vec2 start;
        Vec2 end;
    };

    template<int N>
    struct PolyLine
    {
        static_assert(N > 2);
        Vec2 points[N];
    };

    struct Box
    {
        Vec2 points[4]; // in order of counter clockwise
    };

    class Collision
    {
    public:
        static bool areIntersected(const AxisAlignedBox& box1, const AxisAlignedBox& box2);
        static bool areIntersected(const Disk& disc1, const Disk& disc2);

        static bool areIntersected(const AxisAlignedBox& box, const Disk& disc);


        static inline bool areIntersected(const Disk& disc, const AxisAlignedBox& box) { return areIntersected(box, disc); }
    };
}