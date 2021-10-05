#include "Sprite.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shader.hpp>

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
		states.transform = this->getTransform();
		states.texture = texture;
		states.shader = shader;
		target.draw(verticies, 4, sf::PrimitiveType::TriangleFan, states);
	}

	Sprite::Sprite()
	{
		verticies[0].position = { -0.5f, -0.5f };
		verticies[1].position = { -0.5f, 0.5f };
		verticies[2].position = { 0.5f, 0.5f };
		verticies[3].position = { 0.5f, -0.5f };

		setArea({ 0.f, 0.f }, { 1.f, 1.f });

		if (not shader)
		{
			shader = new sf::Shader();
			shader->loadFromMemory(vsh, fsh);
		}
	}
	Sprite::Sprite(const Texture& t)
		: Sprite()
	{
		this->texture = &t;
	}
	void Sprite::setArea(const vec2& p1, const vec2& p2)
	{
		//*
		verticies[0].texCoords = p1;
		verticies[1].texCoords = { p1.x, p2.y };
		verticies[2].texCoords = p2;
		verticies[3].texCoords = { p2.x, p1.y };/**/
		/*
		verticies[0].texCoords = { p1.x, p2.y };
		verticies[1].texCoords = p1;
		verticies[2].texCoords = { p2.x, p1.y };
		verticies[3].texCoords = p2;/**/
	}
}