#pragma once

#include <memory>
#include <map>
#include <RandomEngine/API/Math/CollisionFunctions.hpp>
#include "Game/Object/SpriteObject.hpp"

using namespace random_engine;

namespace game
{
	const Rect DEF_HITBOX = Rect({ -0.5f, -0.5f }, { 0.5f, 0.5f });

	class SpriteObjectBuilder
	{
		bool is_created = false;
		SpriteObject* object;
	public:
		struct ObjectInfo
		{
			int textureId = 0;
			std::vector<Rect> areas;

			Rect hitbox;
			StaticBody::CollisionMode collisionMode;
			int actionId = 0;

			vec2 size;
		};
		static const std::map<int, ObjectInfo> id_map;
		static StaticBody::Action idToAction(int id);

		SpriteObjectBuilder();
		~SpriteObjectBuilder();

		void setObjectId(int id);
		int getId() const;

		std::unique_ptr<SpriteObject> build() const;
		std::unique_ptr<SpriteObject> build(int id);
	};
	extern SpriteObjectBuilder spriteObjectBuilder;
}