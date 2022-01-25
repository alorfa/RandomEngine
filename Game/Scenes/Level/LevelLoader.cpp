#include "LevelLoader.hpp"

#include <boost/json.hpp>
#include <RandomEngine/API/Resource/File.hpp>
#include "Game/Object/SpriteObject.hpp"
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include "Game/Player.hpp"
#include <RandomEngine/API/GlobalData.hpp>

using namespace boost;

namespace
{
	constexpr u32 OBJECTS_SEGMENTS_X = 10;
	constexpr u32 OBJECTS_SEGMENTS_Y = 10;
	constexpr float OBJ_X_PART = 1.f / (float)OBJECTS_SEGMENTS_X;
	constexpr float OBJ_Y_PART = 1.f / (float)OBJECTS_SEGMENTS_Y;
	const vec2 OBJ_PART = { OBJ_X_PART , OBJ_Y_PART };

	constexpr u32 PORTALS_SEGMENTS_X = 10;
	constexpr float PORT_X_PART = 1.f / (float)PORTALS_SEGMENTS_X;

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
	std::unique_ptr<Object> LevelLoader::createObject(u64 id, const vec2& pos, const Rect& hitbox)
	{
		const auto& res = GlobalData::getInstance().res;

		auto* obj = new SpriteObject;
		std::unique_ptr<Object> result(obj);
		obj->setPosition(pos);
		obj->hitbox = hitbox;
		if (id <= 100)
		{
			obj->load(res / "img/objects.png");
			vec2 area_begin;
			area_begin.x = float(id - 1) / (float)OBJECTS_SEGMENTS_X;
			area_begin.y = 9.f / (float)OBJECTS_SEGMENTS_Y;
			const vec2 area_end = area_begin + OBJ_PART;
			obj->setArea(area_begin, area_end);
		}
		else if (id <= 200)
		{
			const u64 pid = id - 100;
			obj->load(res / "img/portals.png");
			vec2 area_begin;
			area_begin.x = float(pid - 1) / (float)PORTALS_SEGMENTS_X;
			area_begin.y = 0.f;
			const vec2 area_end = area_begin + vec2{ PORT_X_PART, 1.f };
			obj->setArea(area_begin, area_end);
			switch (pid)
			{
			case 1:
				obj->action = [](Player& p) {
					p.game_mode = GameMode::ship;
				};
				break;
			case 2:
				obj->action = [](Player& p) {
					p.game_mode = GameMode::cube;
				};
			}
			obj->collisionMode = StaticBody::Touch;
			obj->setScale({ 1.f, 3.f });
		}
		if (id == 3)
		{
			obj->collisionMode = StaticBody::Touch;
			obj->action = [](Player& p) {
				p.die();
			};
			obj->hitbox.min = { -0.17f, -0.5f };
			obj->hitbox.max = { 0.17f, 0.15f };
		}
		if (id == 4)
		{
			obj->collisionMode = StaticBody::OnClick;
			obj->action = [](Player& p) {
				p.jump(1.f);
			};
		}
		if (id == 5)
		{
			obj->collisionMode = StaticBody::OnClick;
			obj->action = [](Player& p) {
				p.jump(0.6f);
			};
		}
		return std::move(result);
	}
	std::vector<std::unique_ptr<Object>> LevelLoader::handleObjects(const json::value& value)
	{
		std::vector<std::unique_ptr<Object>> result;

		const auto& arr = value.as_array();
		for (const json::value& elem : arr)
		{
			const auto& obj = elem.as_object();
			const json::array& json_pos = obj.at("pos").as_array();
			vec2 pos;
			pos.x = numberAsFloat(json_pos[0]);
			pos.y = numberAsFloat(json_pos[1]);
			const i64 id = obj.at("id").as_int64();
			Rect hitbox({ -0.5f, -0.5f }, { 0.5f, 0.5f });
			vec2 size{ 1.f, 1.f };
			if (obj.contains("rect_hitbox"))
			{
				const json::array& hb = obj.at("rect_hitbox").as_array();
				hitbox.min.x = numberAsFloat(hb[0]);
				hitbox.min.y = numberAsFloat(hb[1]);
				hitbox.max.x = numberAsFloat(hb[2]);
				hitbox.max.y = numberAsFloat(hb[3]);
			}
			std::unique_ptr<Object> object = createObject(id, pos, hitbox);
			if (obj.contains("size"))
			{
				const json::array& sz = obj.at("size").as_array();
				size.x = numberAsFloat(sz[0]);
				size.y = numberAsFloat(sz[1]);
				object->setScale(size);
			}
			result.push_back(std::move(object));
		}

		return result;
	}

	std::pair<vec2, vec2> LevelLoader::handleGrounds(const boost::json::value& value) const
	{
		std::pair<vec2, vec2> result;

		const auto& arr = value.as_array();
		result.first.x = numberAsFloat(arr[0]);
		result.first.y = numberAsFloat(arr[1]);
		result.second.x = numberAsFloat(arr[2]);
		result.second.y = numberAsFloat(arr[3]);

		return result;
	}

	LevelState* LevelLoader::loadFromFile(const std::filesystem::path& path, int flags)
	{
		std::string json_data = File::readTextAsString(path);

		json::parse_options options;
		options.allow_comments = true;
		
		try
		{
			json::value value = json::parse(json_data, {}, options);
			auto [bottom, top] = handleGrounds(value.as_object().at("grounds"));
			auto objects = handleObjects(value.as_object().at("objects"));
			auto* levelState = new LevelState;
			levelState->objects = std::move(objects);
			levelState->bottom_ground = bottom;
			levelState->top_ground = top;
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
	LevelLoader levelLoader;
}