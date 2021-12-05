#pragma once

#include <RandomEngine/API/Resource/ResourceLoader.hpp>
#include "Game/Level/LevelState.hpp"

using namespace random_engine;

namespace game
{
	class LevelLoader : public ResourceLoader
	{
	protected:
		LevelState* loadFromFile(const std::filesystem::path& path, int flags = 0) override;
	public:
		LevelState& getDefault() const override;

		LevelState& load(const std::filesystem::path& path, int flags = 0) override;
	};
}