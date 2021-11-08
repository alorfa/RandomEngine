#pragma once

#include "Game/Player.hpp"

namespace game
{
	class CollisionArea
	{
	public:
		virtual bool touches(const Player&) const = 0;
		virtual StaticBody::RepulsionResult getRepulsionVector(const Player&) const = 0;
	};
}