#pragma once

#include <RandomEngine/API/Resource/ResourceLoader.hpp>
#include "Game/Scenes/Level/LevelState.hpp"

using namespace random_engine;

namespace random_engine
{
	struct Rect;
}
namespace boost::json
{
	class value;
}

namespace game
{
	class LevelLoader : public ResourceLoader
	{
		std::vector<std::unique_ptr<Object>> handleObjects(const boost::json::value& value);
		std::pair<vec2, vec2> handleGrounds(const boost::json::value& value) const;
	public:
		LevelState& getDefault() const override;
		LevelState* loadFromFile(const std::filesystem::path& path, int flags = 0) override;
		LevelState& load(const std::filesystem::path& path, int flags = 0) override;

		static std::unique_ptr<Object> createObject(u64 id, const vec2& pos, const Rect& hitbox);
	};
	extern LevelLoader levelLoader;
}