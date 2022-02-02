#pragma once

#include "SpriteModel.hpp"
#include "RandomEngine/API/Graphics/Object.hpp"

namespace random_engine
{
	class Sprite : public Object
	{
	protected:
		SpriteModel model;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		Sprite();
		Sprite(const Texture& t);
		void setArea(const vec2& min, const vec2& max);

		const Texture& getTexture() const;
		void setTexture(const Texture& t);

		const sf::Color& getColor() const;
		void setColor(const sf::Color& color);

		enum ScaleMode
		{
			MinOne, MaxOne
		};
		void setAlignment(ScaleMode mode);
		void align(ScaleMode mode);

		inline const sf::Vertex* getVertices() const {
			return model.vertices;
		}
		inline sf::Vertex* changeVertices() {
			return model.vertices;
		}
	};
}