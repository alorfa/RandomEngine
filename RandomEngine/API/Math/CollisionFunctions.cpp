#include "CollisionFunctions.hpp"

namespace random_engine
{
    inline float squared(float x) { return x*x; }

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
            auto const square_radius = disc.radius*disc.radius;
            return (box.min - disc.center).square_length() < square_radius ||
                   (box.max - disc.center).square_length() < square_radius ||
                   (Vec2{box.min.x, box.max.y} - disc.center).square_length() < square_radius ||
                   (Vec2{box.max.x, box.min.y} - disc.center).square_length() < square_radius;
        }
        else
            return false;
    }


    bool Collision::areIntersected(const Disk& disc1, const Disk& disc2)
    {
        return (disc1.center - disc2.center).square_length() <= squared(disc1.radius+disc2.radius);
    }

}