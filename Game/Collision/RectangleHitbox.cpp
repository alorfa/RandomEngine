#include "RectangleHitbox.hpp"

namespace game
{
	RectangleHitbox::RectangleHitbox(const vec2& pos, const vec2& size, float rotation)
		: position(pos), size(size), rotation(rotation) {}

	bool RectangleHitbox::touches(const Hitbox& other) const
	{
		const auto* rect = dynamic_cast<const RectangleHitbox*>(&other);
		if (rect)
		{
			return false;
		}
		return false;
	}

	RepulsionResult RectangleHitbox::getRepulsionVector(const Hitbox& other) const
	{
		return RepulsionResult();
	}


}