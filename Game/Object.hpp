#pragma once

#include <vector>
#include <RandomEngine/API/Graphics/Object.hpp>
#include "Game/Collision/StaticBody.hpp"
#include "Game/Object/Group.hpp"
#include "Game/Object/Trigger/ITransformableObject.h"

using namespace random_engine;

namespace game
{
	class Object : public random_engine::Object, public StaticBody, public ITransformableObject
	{
		vec2 prev_position;
	public:
		std::vector<Group> groups;

		vec2 direction;

		void update(float delta);

		inline const vec2& getPrevPos() const {
			return prev_position;
		}

		void moveByTrigger(const vec2& offset) override;
		void rotateByTrigger(float deg) override;
		void scaleByTrigger(const vec2& factor) override;
	};
}