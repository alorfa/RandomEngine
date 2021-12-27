#pragma once

#include <vector>
#include <RandomEngine/API/Resource/ResourceLoader.hpp>
#include "Game/Object.hpp"

namespace game
{
	struct LevelState : public Resource
	{
		std::vector<Object*> objects;
		float top_ground = 7.5f, bottom_ground = -0.5f;
	};
}