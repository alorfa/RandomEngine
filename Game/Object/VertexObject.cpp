#include "VertexObject.hpp"

namespace game
{
	VertexObject::VertexObject(const std::vector<sf::Vertex>& vertices, sf::PrimitiveType drawMode)
		: vertices(vertices), drawMode(drawMode) {}

	VertexObject::VertexObject(sf::PrimitiveType drawMode)
		: drawMode(drawMode) {}

	bool VertexObject::touches(const PhysicalRect&) const
	{
		return false;
	}

	RepulsionResult VertexObject::getRepulsionVector(const PhysicalRect&) const
	{
		return RepulsionResult();
	}

	void VertexObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(vertices.data(), vertices.size(), drawMode, states);
	}

	std::unique_ptr<Object> VertexObject::clone() const
	{
		return std::make_unique<VertexObject>(*this);
	}
}