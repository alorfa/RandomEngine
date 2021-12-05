#pragma once

#include <RandomEngine/API/Resource/ResourceLoader.hpp>
#include "Game/Object.hpp"
#include <vector>

namespace game
{
	struct LevelState : public Resource
	{
		std::vector<Object> objects;
		float top_ground, bottom_ground;
	};
}