#pragma once

#include <Game/Object.hpp>
#include <RandomEngine/API/Graphics/Sprite.hpp>
#include <RandomEngine/API/Math/CollisionFunctions.hpp>

using namespace random_engine;

namespace game
{
	class SpriteObject : public game::Object
	{
		mutable Sprite sprite;
		mutable PhysicalRect physical_rect;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		bool touches(const Player&) const override;
		RepulsionResult getRepulsionVector(const Player&, bool noMovement = false) const override;

		void load(const std::filesystem::path& path);

		const PhysicalRect& getPhysicalRect() const;
	};
}