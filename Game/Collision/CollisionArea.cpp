#include "RectangleArea.hpp"

namespace game
{
	RectangleArea::RectangleArea(const vec2& pos, const vec2& size, float rotation)
		: position(pos), size(size), rotation(rotation) {}

	bool RectangleArea::touches(const Player& p) const
	{
		return false;
	}

	StaticBody::RepulsionResult RectangleArea::getRepulsionVector(const Player& p) const
	{
		return StaticBody::RepulsionResult();
	}


}