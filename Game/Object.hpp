#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "Game/Object/Group.hpp"
#include <vector>

namespace game
{
	class Object : public sf::Drawable
	{
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		std::vector<Group> groups;
	};
}