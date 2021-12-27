#include "LevelLoader.hpp"

#include <boost/json.hpp>
#include <RandomEngine/API/Resource/File.hpp>
#include "Game/Object/SpriteObject.hpp"
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>

using namespace boost;

namespace
{
	constexpr u32 IMAGE_SEGMENTS_X = 10;
	constexpr float IMG_X_PART = 1.f / (float)IMAGE_SEGMENTS_X;
	const vec2 IMG_PART = { IMG_X_PART , IMG_X_PART };

	float numberAsFloat(const json::value& value)
	{
		if (value.is_double())
			return (float)value.as_double();
		if (value.is_int64())
			return (float)value.as_int64();
		return (float)value.as_uint64();
	}
}

namespace game
{
	Object* LevelLoader::createObject(u64 id, const vec2& pos)
	{
		vec2 area_begin;
		area_begin.x = float(id - 1) / (float)IMAGE_SEGMENTS_X;
		area_begin.y = 9.f / (float)IMAGE_SEGMENTS_X;
		const vec2 area_end = area_begin + IMG_PART;

		auto* obj = new game::SpriteObject;
		obj->setPosition(pos);
		obj->load((*res) / "img/objects.png");
		obj->setArea(area_begin, area_end);
		return obj;
	}
	std::vector<Object*> LevelLoader::handleObjects(const json::value& value)
	{
		std::vector<game::Object*> result;

		const auto& arr = value.as_array();
		for (const json::value& elem : arr)
		{
			const auto& obj = elem.as_object();
			const json::array& json_pos = obj.at("pos").as_array();
			vec2 pos;
			pos.x = numberAsFloat(json_pos[0]);
			pos.y = numberAsFloat(json_pos[1]);
			const i64 id = obj.at("id").as_int64();
			result.push_back(createObject(id, pos));
		}

		return result;
	}
	LevelState* LevelLoader::loadFromFile(const std::filesystem::path& path, int flags)
	{
		std::string json_data = File::readTextAsString(path);

		/*json::parse_options options;
		options.allow_comments = true;
		json::storage_ptr sp;*/
		
		try
		{
			json::value value = json::parse(json_data);

			auto objects = handleObjects(value.as_object().at("objects"));
			auto* levelState = new LevelState;
			levelState->objects = std::move(objects);
			return levelState;
		}
		catch (...)
		{
			return nullptr;
		}
	}
	LevelState& LevelLoader::getDefault() const
	{
		static LevelState defaultLevel;
		return defaultLevel;
	}
	LevelState& LevelLoader::load(const std::filesystem::path& path, int flags)
	{
		return static_cast<LevelState&>(defaultLoad(path, flags));
	}
	void LevelLoader::setResourcesPath(const std::filesystem::path& path)
	{
		res = &path;
	}
	LevelLoader levelLoader;
}