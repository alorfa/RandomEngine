#include "SpriteModel.hpp"

namespace random_engine
{
	SpriteModel::SpriteModel()
	{
		vertices[0].position = { -0.5f, -0.5f };
		vertices[1].position = { -0.5f, 0.5f };
		vertices[2].position = { 0.5f, 0.5f };
		vertices[3].position = { 0.5f, -0.5f };

		setArea({ 0.f, 0.f }, { 1.f, 1.f });
	}
	void SpriteModel::setArea(const vec2& min, const vec2& max)
	{
		vertices[0].texCoords = min;
		vertices[1].texCoords = { min.x, max.y };
		vertices[2].texCoords = max;
		vertices[3].texCoords = { max.x, min.y };
	}
	const sf::Color& SpriteModel::getColor() const
	{
		return vertices->color;
	}
	void SpriteModel::setColor(const sf::Color& color)
	{
		for (auto& vert : vertices)
			vert.color = color;
	}
}