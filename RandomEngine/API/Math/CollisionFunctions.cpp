#include "CollisionFunctions.hpp"

namespace random_engine
{
	bool Collision::RectTouchesRect(const Rect& cube, const Rect& rect)
	{
		return (
			cube.p2.x >= rect.p1.x &&
			cube.p1.x <= rect.p2.x &&
			cube.p2.y >= rect.p1.y &&
			cube.p1.y <= rect.p2.y);
	}

}