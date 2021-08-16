#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <RandomEngine/API/Math/vec2.hpp>

namespace random_engine
{
	class Circle : public sf::Drawable, public sf::Transformable
	{
		sf::VertexArray verticies;
		int vertex_count = 0;

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:
		Circle() = default;
		Circle(int vert_count, const vec2& size = { 1, 1 });
		void create(int vert_count, const vec2& size = { 1, 1 });
	};
}