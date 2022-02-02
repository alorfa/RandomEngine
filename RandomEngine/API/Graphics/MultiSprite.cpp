#include "MultiSprite.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <RandomEngine/API/Resource/TextureLoader.hpp>
#include "DefaultShaders.hpp"

namespace random_engine
{
	MultiSprite::MultiSprite()
	{
		setCount(1);
	}

	void MultiSprite::setCount(size_t s) {
		models.resize(s);
	}
	size_t MultiSprite::getCount() const {
		return models.size();
	}
	const SpriteModel& MultiSprite::operator[](size_t i) const {
		return models.at(i);
	}
	SpriteModel& MultiSprite::operator[](size_t i)	{
		return models.at(i);
	}
	void MultiSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		if (not states.shader)
			states.shader = DefaultShaders::getSpriteShader();

		for (const auto& model : models)
		{
			states.texture = model.texture;
			target.draw(model.vertices, 4, sf::TrianglesFan, states);
		}
	}
	void MultiSprite::drawReverse(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		if (not states.shader)
			states.shader = DefaultShaders::getSpriteShader();

		for (auto it = models.crbegin(); it != models.crend(); ++it)
		{
			states.texture = it->texture;
			target.draw(it->vertices, 4, sf::TrianglesFan, states);
		}
	}
}