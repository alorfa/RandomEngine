#pragma once

#include <RandomEngine/API/Math/vec2.hpp>
#include <RandomEngine/API/Math/RepulsionResult.hpp>

namespace random_engine
{
	struct PhysicalRect;
}

using namespace random_engine;

namespace game
{
	class Player;

	class StaticBody
	{
	public:
		enum CollisionMode
		{
			// returns success and direction, where player will push off
			Repulsion, 
			// returns only success, may user with object action
			Touch,
			OnClick,
			// nothing reaction
			None
		}; 
		using Action = void (*)(Player&); 

		Action action = nullptr;
		CollisionMode collisionMode = Repulsion;

		virtual bool touches(const PhysicalRect&) const = 0;
		virtual RepulsionResult getRepulsionVector(const PhysicalRect&) const = 0;
	};
}