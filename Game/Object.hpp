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
	public:
		std::vector<Group> groups;

		void update(float delta);
	};
}