#pragma once

#include <RandomEngine/API/Scene.hpp>
#include "Game/Scenes/Level/Bound.hpp"
#include "Game/Scenes/Level/Background.hpp"
#include <filesystem>

using namespace random_engine;

namespace game
{
	class LevelBase : public Scene
	{
	public:
		Bound top, bottom;
		Background bg;

		LevelBase();

		void loadBounds(const std::filesystem::path& path);
		void loadBackground(const std::filesystem::path& path);

		void drawGrid(sf::RenderTarget& target, const sf::RenderStates& states) const;
	};
}