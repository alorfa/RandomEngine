#pragma once

#include <RandomEngine/API/Math/vec2.hpp>

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
			// nothing reaction
			None
		}; 
		struct RepulsionResult {
			bool touches;
			vec2 direction;

			inline RepulsionResult()
				: touches(false), direction() {}
		};
		using Action = void (*)(Player&); 

		Action action = nullptr;
		CollisionMode collisionMode;

		virtual bool touches(const Player&) const = 0;
		virtual RepulsionResult getRepulsionVector(const Player&) const = 0;
	};
}