#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <RandomEngine/API/Math/vec2.hpp>
#include <RandomEngine/API/Graphics/Camera.hpp>

namespace random_engine
{
	class Circle : public sf::Drawable, public sf::Transformable
	{
	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:
	};
}