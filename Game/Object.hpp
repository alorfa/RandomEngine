#pragma once

#include <vector>
#include <RandomEngine/API/Graphics/GameObjectBase.hpp>
#include "Game/Collision/StaticBody.hpp"
#include "Game/Object/Group.hpp"
#include "Game/Object/Trigger/ITransformableObject.h"
#include <RandomEngine/API/Math/CollisionFunctions.hpp>

using namespace random_engine;

namespace game
{
	class Object : public GameObjectBase, public StaticBody, public ITransformableObject
	{
		vec2 prev_position;
	protected:
		mutable PhysicalRect physical_rect;
		mutable sf::Vertex hitbox_vertices[5];
	public:
		Rect hitbox;
		//std::vector<Group> groups;

		vec2 direction;

		bool is_selected = false;

		void update(float delta);

		inline const vec2& getPrevPos() const {
			return prev_position;
		}

		void moveByTrigger(const vec2& offset) override;
		void rotateByTrigger(float deg) override;
		void scaleByTrigger(const vec2& factor) override;

		void drawHitbox(sf::RenderTarget& target, sf::RenderStates states) const;

		virtual std::unique_ptr<Object> clone() const = 0;
	};
}