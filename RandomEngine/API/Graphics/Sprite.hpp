#pragma once

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <RandomEngine/API/Math/vec2.hpp>
#include <RandomEngine/API/Resource/TextureLoader.hpp>

namespace random_engine
{
	class Sprite : public sf::Transformable, public sf::Drawable
	{
		inline static sf::Shader* shader = nullptr;
		sf::Vertex verticies[4];
	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		const Texture* texture = nullptr;

		Sprite();
		Sprite(const Texture& t);
		void setArea(const vec2& p1, const vec2& p2);
	};
}