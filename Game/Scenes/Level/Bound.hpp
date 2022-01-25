#pragma once

#include <RandomEngine/API/Graphics/Sprite.hpp>
#include <RandomEngine/API/Graphics/Camera.hpp>
#include "Game/Collision/StaticBody.hpp"
#include "Game/Object/Trigger/ITransformableObject.h"

using namespace random_engine;

namespace game
{
	class Bound : public sf::Drawable, public StaticBody, public IMoveableObject
	{
		mutable Sprite sprite;

		static constexpr int SEGMENT_SIZE = 4;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		enum Location {
			Top, Bottom
		};
	private:
		Location location;
	public:
		vec2 pos;

		Bound(Location location);

		void setTexture(const Texture& t);

		bool touches(const PhysicalRect&) const override;
		RepulsionResult getRepulsionVector(const PhysicalRect&) const override;

		void moveByTrigger(const vec2& offset) override;
	};
}