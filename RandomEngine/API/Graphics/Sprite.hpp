#pragma once

#include <SFML/Graphics/Vertex.hpp>
#include "RandomEngine/API/Math/vec2.hpp"
#include "RandomEngine/API/Resource/TextureLoader.hpp"
#include "RandomEngine/API/Graphics/Object.hpp"

namespace random_engine
{
	class Sprite : public Object
	{
		inline static sf::Shader* shader = nullptr;
	protected:
		sf::Vertex vertices[4];
		const Texture* texture = nullptr;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		Sprite();
		Sprite(const Texture& t);
		void setArea(const vec2& p1, const vec2& p2);

		const Texture& getTexture() const;
		void setTexture(const Texture& t);

		enum ScaleMode
		{
			MinOne, MaxOne
		};
		void setAlignment(ScaleMode mode);
		void align(ScaleMode mode);

		inline const sf::Vertex* getVertices() const {
			return vertices;
		}
		inline sf::Vertex* changeVertices() {
			return vertices;
		}
	};
}