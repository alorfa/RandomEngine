#include "Sprite.hpp"
#include "RandomEngine/API/Resource/TextureLoader.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <cmath>

namespace
{
	const char* vsh = R"raw(
void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    // transform the texture coordinates
	gl_TexCoord[0] = gl_MultiTexCoord0;

    // forward the vertex color
    gl_FrontColor = gl_Color;
})raw";
	const char* fsh = R"raw(
uniform sampler2D texture;

void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color
    gl_FragColor = gl_Color * pixel;
})raw";
}

namespace random_engine
{
	void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = texture;
		if (not states.shader)
			states.shader = shader;
		target.draw(vertices, 4, sf::TriangleFan, states);
	}

	Sprite::Sprite()
		: Sprite(textureLoader.getDefault())
	{}

	Sprite::Sprite(const Texture& t)
	{
		vertices[0].position = { -0.5f, -0.5f };
		vertices[1].position = { -0.5f, 0.5f };
		vertices[2].position = { 0.5f, 0.5f };
		vertices[3].position = { 0.5f, -0.5f };

		setArea({ 0.f, 0.f }, { 1.f, 1.f });

		setTexture(t);

		if (not shader)
		{
			shader = new sf::Shader();
			shader->loadFromMemory(vsh, fsh);
		}
	}
	void Sprite::setArea(const vec2& p1, const vec2& p2)
	{
		vertices[0].texCoords = p1;
		vertices[1].texCoords = { p1.x, p2.y };
		vertices[2].texCoords = p2;
		vertices[3].texCoords = { p2.x, p1.y };
	}
	const Texture& Sprite::getTexture() const
	{
		return *texture;
	}
	void Sprite::setTexture(const Texture& t)
	{
		this->texture = &t;
	}
	const sf::Color& Sprite::getColor() const
	{
		return vertices->color;
	}
	void Sprite::setColor(const sf::Color& color)
	{
		for (auto& vert : vertices)
			vert.color = color;
	}
	void Sprite::setAlignment(ScaleMode mode)
	{
		const vec2 size = texture->getSize();
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