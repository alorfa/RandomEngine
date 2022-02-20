#pragma once

#include <RandomEngine/API/Resource/ResourceLoader.hpp>
#include "Game/Scenes/Level/LevelState.hpp"

using namespace random_engine;

namespace game
{
	class DevLevel;

	class BinaryLevelLoader : public ResourceLoader
	{
	public:
		LevelState& getDefault() const override;
		LevelState* loadFromFile(const std::filesystem::path& path, int flags = 0) override;
		LevelState& load(const std::filesystem::path& path, int flags = 0) override;
		void saveToFile(const std::filesystem::path& path, const DevLevel& level);
	};
	extern BinaryLevelLoader binaryLevelLoader;
}