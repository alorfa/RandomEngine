#pragma once

#include <vector>
#include "Game/Object.hpp"
#include <SFML/Graphics/Vertex.hpp>

namespace game
{
	class ProcessGroup
	{
		std::vector<Object*> objects;
		std::vector<sf::Vertex*> verticies;
		Group group;
	public:
	};
}