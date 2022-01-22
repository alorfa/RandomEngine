#pragma once

#include "Game/Player.hpp"

namespace game
{
	class Hitbox
	{
	public:
		virtual bool touches(const Hitbox&) const = 0;
		virtual RepulsionResult getRepulsionVector(const Hitbox&) const = 0;
	};
}