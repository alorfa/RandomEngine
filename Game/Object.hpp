#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "Game/Object/Group.hpp"
#include <vector>

namespace game
{
	class Object : public sf::Drawable, public sf::Transformable
	{
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
	public:
		std::vector<Group> groups;

		virtual ~Object() = default;
	};
}