#pragma once

#include <RandomEngine/API/Math/CollisionFunctions.hpp>
#include <RandomEngine/API/Graphics/GameObjectBase.hpp>

using namespace random_engine;

namespace game
{
	class StaticBody;

	class DynamicBody : public GameObjectBase
	{
	protected:
		mutable PhysicalRect physical_rect, death_area;
		mutable sf::Vertex hitbox_vertices[5];
		mutable sf::Vertex death_area_vertices[5];

		bool onGround = false;

		vec2 prev_position = vec2();

		std::vector<vec2> contact_offsets;
	public:
		vec2 direction;

		bool isOnGround() const;

		void collisionBegin();
		void collisionProcess(const StaticBody& bodies);
		// returns true is the cube can collide
		bool testCollisions(const StaticBody& bodies) const;
		inline const vec2& getPrevPos() const {
			return prev_position;
		}
		void collisionEnd();

		const PhysicalRect& getPhysicalRect() const;
		const PhysicalRect& getDeathArea() const;
		const std::vector<vec2>& getContactOffsets() const;

		template <typename T>
		bool is() const
		{
			return dynamic_cast<const T*>(this);
		}
		template <typename T>
		T& as()
		{
			return dynamic_cast<T&>(*this);
		}
	};
}