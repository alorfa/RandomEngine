#include "Shape.hpp"
#include "RandomEngine/API/Math/Functions.hpp"

namespace random_engine
{
	std::vector<sf::Vertex> Shape::createCircle(size_t vertCount, const Vec2& size)
	{
		/* Additional (with index 0) point is the center of the circle,
		* last point is the copy of the first (with index 1) the circle point
		*/
		std::vector<sf::Vertex> verts(vertCount + 2);
		verts[0].position = { 0.f, 0.f };
		for (size_t i = 1; i < vertCount + 2; i++)
			verts[i].position = Math::getCirclePoint((i - 1) * (Math::TAU / vertCount), size * 0.5f);
		return verts;
	}
	size_t Shape::getShapeCount(size_t vertCount, sf::PrimitiveType drawMode)
	{
		if (vertCount == 0)
			return 0;

		switch (drawMode)
		{
		case sf::Points:
			return vertCount;
		case sf::Lines:
			return vertCount / 2;
		case sf::LinesStrip:
			return vertCount - 1;
		case sf::Triangles:
			return vertCount / 3;
		case sf::TriangleStrip:
		case sf::TriangleFan:
			if (vertCount < 3)
				return 0;
			return vertCount - 2;
		case sf::Quads:
			return vertCount / 4;
		}
		return 0;
	}
	size_t Shape::getVertexCount(size_t shapeCount, sf::PrimitiveType drawMode)
	{
		if (shapeCount == 0)
			return 0;

		switch (drawMode)
		{
		case sf::Points:
			return shapeCount;
		case sf::Lines:
			return shapeCount * 2;
		case sf::Triangles:
			return shapeCount * 3;
		case sf::Quads:
			return shapeCount * 4;
		case sf::LineStrip:
			return shapeCount + 1;
		case sf::TriangleStrip:
		case sf::TriangleFan:
			return shapeCount + 2;
		}
		return 0;
	}
}