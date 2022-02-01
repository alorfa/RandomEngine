#pragma once

#include <SFML/Graphics/Vertex.hpp>
#include "RandomEngine/API/Resource/TextureLoader.hpp"
#include "RandomEngine/API/Math/vec2.hpp"

namespace random_engine
{
	class SpriteModel
	{
	public:
		SpriteModel();

		sf::Vertex vertices[4];
		const Texture* texture = nullptr;

		void setArea(const vec2& min, const vec2& max);

		const sf::Color& getColor() const;
		void setColor(const sf::Color& color);
	};
}