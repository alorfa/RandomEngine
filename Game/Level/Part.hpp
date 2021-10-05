#pragma once

#include "Game/Object.hpp"
#include "Game/Object/ProcessGroup.hpp"

namespace game
{
	class Part
	{
		std::vector<ProcessGroup> groups;
	};
}