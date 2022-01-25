#pragma once

#include <RandomEngine/API/Graphics/Sprite.hpp>
#include "Game/Object/Trigger/ITransformableObject.h"

using namespace random_engine;

namespace game
{
	class Background : public sf::Drawable, public IMoveableObject
	{
		static constexpr float SIZE = 50.f;

		mutable Sprite sprite;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		vec2 pos;

		void setTexture(const Texture& t);

		void moveByTrigger(const fvec2& offset) override;
	};
}