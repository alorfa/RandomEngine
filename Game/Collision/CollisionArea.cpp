#include "RectangleArea.hpp"

namespace game
{
	RectangleArea::RectangleArea(const Vec2& pos, const Vec2& size, float rotation)
		: position(pos), size(size), rotation(rotation) {}

	bool RectangleArea::touches(const Player& p) const
	{
		return false;
	}

	RepulsionResult RectangleArea::getRepulsionVector(const Player& p) const
	{
		return RepulsionResult();
	}


}