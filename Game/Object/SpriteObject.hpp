#pragma once

#include <Game/Object.hpp>
#include <RandomEngine/API/Graphics/Sprite.hpp>

using namespace random_engine;

namespace game
{
	class SpriteObject : public game::Object
	{
		mutable Sprite sprite;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		bool touches(const Player&) const override;
		RepulsionResult getRepulsionVector(const Player&) const override;

		void load(const std::filesystem::path& path);
	};
}