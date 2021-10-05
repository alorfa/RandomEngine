#pragma once

#include "Game/Object.hpp"
#include "SFML/Graphics/VertexArray.hpp"

namespace game
{
	class VertexObject : public Object
	{
	public:
		sf::VertexArray verticies;
		std::vector<Group> vert_groups;
		
	};
}