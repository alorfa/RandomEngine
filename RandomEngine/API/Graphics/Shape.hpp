#pragma once

#include <vector>
#include <SFML/Graphics/Vertex.hpp>
#include "RandomEngine/API/Math/vec2.hpp"
#include <SFML/Graphics/PrimitiveType.hpp>

namespace random_engine
{
	class Shape
	{
	public:
		static std::vector<sf::Vertex> createCircle(size_t vertCount = 20, const vec2& size = { 1.f, 1.f });
		// returns the shape count with a given number of vertices and a primitive type 
		static size_t getShapeCount(size_t vertCount, sf::PrimitiveType);
		// returns the vertices count with a given number of shapes and a primitive type 
		static size_t getVertexCount(size_t shapeCount, sf::PrimitiveType);
	};
}