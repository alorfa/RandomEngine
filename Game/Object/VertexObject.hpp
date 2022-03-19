#pragma once

#include "Game/Object.hpp"
#include "SFML/Graphics/VertexArray.hpp"

namespace game
{
	class VertexObject : public Object
	{
	public:
		std::vector<sf::Vertex> vertices;
		sf::PrimitiveType drawMode;

		VertexObject(const std::vector<sf::Vertex>& vertices, sf::PrimitiveType drawMode);
		VertexObject(sf::PrimitiveType drawMode);

		bool touches(const PhysicalRect&) const override;
		RepulsionResult getRepulsionVector(const PhysicalRect&) const override;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		std::unique_ptr<Object> clone() const override;
	};
}