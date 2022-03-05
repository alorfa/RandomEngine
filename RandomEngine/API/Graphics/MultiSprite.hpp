#pragma once

#include "RandomEngine/API/Graphics/Object.hpp"
#include "RandomEngine/API/Graphics/SpriteModel.hpp"
#include <vector>

namespace random_engine
{
	class MultiSprite : public GameObjectBase
	{
		std::vector<SpriteModel> models;
	public:
		MultiSprite();

		void setCount(size_t s);
		size_t getCount() const;

		const SpriteModel& operator[](size_t i) const;
		SpriteModel& operator[](size_t i);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void drawReverse(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}