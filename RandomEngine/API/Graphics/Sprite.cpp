#include "Sprite.hpp"
#include "RandomEngine/API/Resource/TextureLoader.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <cmath>
#include "DefaultShaders.hpp"

namespace random_engine
{
	void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = model.texture;
		if (not states.shader)
			states.shader = DefaultShaders::getSpriteShader();
		target.draw(model.vertices, 4, sf::TriangleFan, states);
	}

	Sprite::Sprite()
		: Sprite(textureLoader.getDefault())
	{}

	Sprite::Sprite(const Texture& t)
	{
		model.vertices[0].position = { -0.5f, -0.5f };
		model.vertices[1].position = { -0.5f, 0.5f };
		model.vertices[2].position = { 0.5f, 0.5f };
		model.vertices[3].position = { 0.5f, -0.5f };

		setArea({ 0.f, 0.f }, { 1.f, 1.f });

		setTexture(t);
	}
	void Sprite::setArea(const vec2& p1, const vec2& p2)
	{
		model.setArea(p1, p2);
	}
	const Texture& Sprite::getTexture() const
	{
		return *model.texture;
	}
	void Sprite::setTexture(const Texture& t)
	{
		model.texture = &t;
	}
	const sf::Color& Sprite::getColor() const
	{
		return model.vertices->color;
	}
	void Sprite::setColor(const sf::Color& color)
	{
		model.setColor(color);
	}
	void Sprite::setAlignment(ScaleMode mode)
	{
		const vec2 size = model.texture->getSize();
		float scaleFactor = 1.f;
		switch (mode)
		{
		case MinOne:
			scaleFactor = std::min(size.x, size.y);
			break;
		case MaxOne:
			scaleFactor = std::max(size.x, size.y);
			break;
		}
		setScale(size.x / scaleFactor, size.y / scaleFactor);
	}
	void Sprite::align(ScaleMode mode)
	{
		auto prev_scale = getScale();
		setAlignment(mode);
		scale(prev_scale);
	}
}