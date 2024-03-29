#pragma once

#include <vector>
#include <RandomEngine/API/Resource/ResourceLoader.hpp>
#include "Game/Object.hpp"

namespace game
{
	struct LevelState : public Resource
	{
		std::vector<std::unique_ptr<Object>> objects;
		vec2 top_ground = { 0.f, 7.5f }, bottom_ground = { 0.f, -0.5f };
		vec2 bg_pos;
	};
}