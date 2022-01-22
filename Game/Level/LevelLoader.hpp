#pragma once

#include <RandomEngine/API/Resource/ResourceLoader.hpp>
#include "Game/Level/LevelState.hpp"

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
		Object* createObject(u64 id, const vec2& pos, const Rect& hitbox);
		std::vector<Object*> handleObjects(const boost::json::value& value);
		std::pair<vec2, vec2> handleGrounds(const boost::json::value& value);
	public:
		LevelState& getDefault() const override;
		LevelState* loadFromFile(const std::filesystem::path& path, int flags = 0) override;
		LevelState& load(const std::filesystem::path& path, int flags = 0) override;
	};
	extern LevelLoader levelLoader;
}