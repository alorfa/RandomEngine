#include "VertexObject.hpp"
#include "RandomEngine/API/Math/Functions.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "RandomEngine/API/Graphics/Shape.hpp"

namespace random_engine
{
	void VertexObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		if (drawVertCount < 0)
			target.draw(vertices.data(), vertices.size(), drawMode, states);
		else
			target.draw(vertices.data(), drawVertCount, drawMode, states);
	}
	VertexObject::VertexObject(sf::PrimitiveType drawMode, int drawVertCount)
		: drawMode(drawMode), drawVertCount(drawVertCount)
	{
	}
	VertexObject::VertexObject(const std::vector<sf::Vertex>& verticies,
		sf::PrimitiveType drawMode, int drawVertCount)
		: vertices(verticies), drawMode(drawMode), drawVertCount(drawVertCount)
	{
	}
	size_t VertexObject::getShapeCount() const
	{
		return Shape::getShapeCount(vertices.size(), drawMode);
	}
}