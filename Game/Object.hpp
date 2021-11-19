#pragma once

#include <RandomEngine/API/Graphics/Object.hpp>
#include "Game/Collision/StaticBody.hpp"
#include "Game/Object/Group.hpp"
#include <vector>

using namespace random_engine;

namespace game
{
	class Object : public random_engine::Object, public StaticBody
	{
		vec2 prev_position;
	public:
		std::vector<Group> groups;

		void update(float delta);

		inline const vec2& getPrevPos() const {
			return prev_position;
		}
	};
}