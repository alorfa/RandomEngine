#include "SpriteObjectBuilder.hpp"
#include <RandomEngine/API/GlobalData.hpp>
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include "Game/Object/ObjectActions.hpp"

namespace
{
	using CMode = game::StaticBody::CollisionMode;

	inline std::pair<int, game::SpriteObjectBuilder::ObjectInfo> pair(int id,
		const vec2& min, int texture_id,
		const Rect& hitbox, CMode collisionMode = CMode::Repulsion, int actionId = 0,
		const vec2& size = { 1.f, 1.f })
	{
		std::pair<int, game::SpriteObjectBuilder::ObjectInfo> result;
		result.first = id;
		result.second.areas.resize(1);
		result.second.areas[0].min = min;
		switch (texture_id)
		{
		case 1:
			result.second.areas[0].max = min + vec2{ 0.1f, 0.1f };
			break;
		case 2:
			result.second.areas[0].max = min + vec2{ 0.1f, 1.f };
			break;
		}
		result.second.textureId = texture_id;
		result.second.size = size;
		result.second.hitbox = hitbox;
		result.second.actionId = actionId;
		result.second.collisionMode = collisionMode;
		return result;
	}
	inline std::pair<int, game::SpriteObjectBuilder::ObjectInfo> pair(int id,
		std::vector<vec2> mins, int texture_id,
		const Rect& hitbox, CMode collisionMode = CMode::Repulsion, int actionId = 0,
		const vec2& size = {1.f, 1.f})
	{
		std::pair<int, game::SpriteObjectBuilder::ObjectInfo> result;
		result.first = id;
		result.second.areas.resize(mins.size());
		for (size_t i = 0; i < mins.size(); i++)
		{
			const vec2& min = mins[i];
			result.second.areas[i].min = min;
			switch (texture_id)
			{
			case 1:
				result.second.areas[i].max = min + vec2{ 0.1f, 0.1f };
				break;
			case 2:
				result.second.areas[i].max = min + vec2{ 0.1f, 1.f };
				break;
			}
		}
		result.second.textureId = texture_id;
		result.second.size = size;
		result.second.hitbox = hitbox;
		result.second.actionId = actionId;
		result.second.collisionMode = collisionMode;
		return result;
	}
	std::map<int, game::SpriteObjectBuilder::ObjectInfo> createMap()
	{
		const Rect HITBOX = Rect({ -0.5f, -0.5f }, { 0.5f, 0.5f });

		std::map<int, game::SpriteObjectBuilder::ObjectInfo> result;
		result.insert({
			pair(1, vec2{0.f, 0.9f}, 1, HITBOX),
			pair(2, vec2{0.1f, 0.9f}, 1, HITBOX),
			pair(3, { vec2{0.2f, 0.9f}, vec2{0.2f, 0.8f}}, 1, Rect({ -0.17f, -0.5f }, { 0.17f, 0.15f }), CMode::Touch, 1),
			pair(4, vec2{0.3f, 0.9f}, 1, HITBOX, CMode::OnClick, 2),
			pair(5, vec2{0.4f, 0.9f}, 1, HITBOX, CMode::OnClick, 3),
			pair(101, vec2{0.f, 0.f}, 2, HITBOX, CMode::Touch, 4, vec2{1.f, 3.f}),
			pair(102, vec2{0.1f, 0.f}, 2, HITBOX, CMode::Touch, 5, vec2{1.f, 3.f})
			});
		return result;
	}
}

namespace game
{
	const std::map<int, SpriteObjectBuilder::ObjectInfo> SpriteObjectBuilder::id_map = createMap();

	StaticBody::Action SpriteObjectBuilder::idToAction(int id)
	{
		switch (id)
		{
		case 1: return ObjectActions::die; 
		case 2: return ObjectActions::normalJump;
		case 3: return ObjectActions::littleJump;
		case 4: return ObjectActions::toShip;
		case 5: return ObjectActions::toCube;
		default:
			DEBUG("ACTION ID FAILED");
		}
	}

	SpriteObjectBuilder::SpriteObjectBuilder()
	{
	}
	SpriteObjectBuilder::~SpriteObjectBuilder()
	{
		delete object;
	}
	void SpriteObjectBuilder::setObjectId(int id)
	{
		if (not is_created) {
			object = new SpriteObject(0);
			is_created = true;
		}

		if (object->id == id)
			return;

		object->id = id;
		const auto& info = id_map.at(id);
		object->setColorCount(info.areas.size());
		switch (info.textureId)
		{
		case 1:
			object->load(res / "img/objects.png");
			break;
		case 2:
			object->load(res / "img/portals.png");
			break;
		default:
			DEBUG("TEXTURE ID FAILED");
		}
		for (size_t i = 0; i < info.areas.size(); i++)
			object->setArea(i, info.areas[i].min, info.areas[i].max);

		object->setScale(info.size);

		object->hitbox = info.hitbox;
		object->collisionMode = info.collisionMode;
		if (object->collisionMode == StaticBody::OnClick or
			object->collisionMode == StaticBody::Touch)
			object->action = idToAction(info.actionId);
	}
	int SpriteObjectBuilder::getId() const
	{
		return object->id;
	}
	std::unique_ptr<SpriteObject> SpriteObjectBuilder::build() const
	{
		return std::make_unique<SpriteObject>(*object);
	}
	std::unique_ptr<SpriteObject> SpriteObjectBuilder::build(int id)
	{
		setObjectId(id);
		return build();
	}
	SpriteObjectBuilder spriteObjectBuilder;
}