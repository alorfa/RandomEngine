#pragma once

#include <RandomEngine/API/Graphics/Sprite.hpp>
#include <RandomEngine/API/Graphics/Camera.hpp>
#include "Game/Collision/StaticBody.hpp"

using namespace random_engine;

namespace game
{
	class Bound : public sf::Drawable, public StaticBody
	{
		mutable Sprite sprite;

		static constexpr int SEGMENT_SIZE = 4;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		const Camera* camera;
	public:
		enum Location {
			Top, Bottom
		};
	private:
		Location location;
	public:
		float posY = 0.f;

		Bound(Location location, const Camera& camera);

		void setTexture(const Texture& t);

		bool touches(const Player&) const override;
		RepulsionResult getRepulsionVector(const Player&) const override;
	};
}