#pragma once

#include <vector>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include "RandomEngine/API/Graphics/GameObjectBase.hpp"
#include "RandomEngine/API/System/types.hpp"

namespace random_engine
{
	struct VertexObject : public GameObjectBase
	{
	protected:
		void draw(sf::RenderTarget&, sf::RenderStates states) const override;
	public:
		std::vector<sf::Vertex> vertices;
		sf::PrimitiveType drawMode;
		// -1 => draw all verticies
		int drawVertCount = -1;

		VertexObject(sf::PrimitiveType drawMode = sf::TriangleFan, int drawVertCount = -1);
		VertexObject(const std::vector<sf::Vertex>& verticies,
			sf::PrimitiveType drawMode = sf::TriangleFan, int drawVertCount = -1);

		size_t getShapeCount() const;
	};
}