#include "SpriteObject.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include <RandomEngine/API/Auxiliary/print_vectors.hpp>
#include <RandomEngine/API/Graphics/Shape.hpp>
#include <RandomEngine/API/Math/CollisionFunctions.hpp>
#include <RandomEngine/API/Resource/TextureLoader.hpp>
#include "Game/Player.hpp"
#include "Game/Settings.hpp"

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
    gl_FragColor = gl_Color * pixel * vec4(0, 1, 0, 1);
})raw";
}

namespace game
{
	void SpriteObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		if (is_selected) {
			states.shader = select_shader;
		}
		
		sprite.drawReverse(target, states);
		//target.draw(sprite, states);
	}
	SpriteObject::SpriteObject()
	{
		hitbox.min = { -0.5f, -0.5f };
		hitbox.max = { 0.5f, 0.5f };

		for (auto& vert : hitbox_vertices)
			vert.color = { 0, 0, 255 };

		if (not select_shader)
		{
			select_shader = new sf::Shader;
			select_shader->loadFromMemory(vsh, fsh);
		}
	}

	bool SpriteObject::touches(const PhysicalRect& rect) const
	{
		return Collision::areIntersected(rect, getCollisionRect());
	}
	RepulsionResult SpriteObject::getRepulsionVector(const PhysicalRect& rect) const
	{
		return Collision::collide(rect, getPhysicalRect());
	}
	void SpriteObject::load(const std::filesystem::path& path)
	{
		for (size_t i = 0; i < sprite.getCount(); ++i)
			sprite[i].texture = &textureLoader.load(path);
	}
	void SpriteObject::setColorCount(size_t count)
	{
		sprite.setCount(count);
	}
	size_t SpriteObject::getColorCount() const
	{
		return sprite.getCount();
	}
	void SpriteObject::setArea(size_t number, const vec2& p1, const vec2& p2)
	{
		sprite[number].setArea(p1, p2);
	}
	void SpriteObject::setColor(size_t number, const sf::Color& color)
	{
		sprite[number].setColor(color);
	}
	const PhysicalRect& SpriteObject::getPhysicalRect() const
	{
		physical_rect.direction = direction;
		physical_rect.center = getPosition();
		physical_rect.min = hitbox.min * getScale() + getPosition();
		physical_rect.max = hitbox.max * getScale() + getPosition();
		physical_rect.movement = getPosition() - getPrevPos(); 
		if (physical_rect.min.x > physical_rect.max.x)
			std::swap(physical_rect.min.x, physical_rect.max.x);
		if (physical_rect.min.y > physical_rect.max.y)
			std::swap(physical_rect.min.y, physical_rect.max.y);
		return physical_rect;
	}
	Rect SpriteObject::getCollisionRect() const
	{
		Rect result{
			hitbox.min * getScale() + getPosition(),
			hitbox.max * getScale() + getPosition()
		};
		if (result.min.x > result.max.x)
			std::swap(result.min.x, result.max.x);
		if (result.min.y > result.max.y)
			std::swap(result.min.y, result.max.y);
		return result;
	}
	std::unique_ptr<Object> SpriteObject::clone() const
	{
		return std::make_unique<SpriteObject>(*this);
	}

	sf::Shader* SpriteObject::select_shader = nullptr;
}