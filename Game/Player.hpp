#pragma once

#include <RandomEngine/API/Graphics/Object.hpp>
#include <RandomEngine/API/Graphics/Sprite.hpp>
#include <RandomEngine/API/Math/color.hpp>
#include <RandomEngine/API/Math/CollisionFunctions.hpp>
#include "Game/Collision/StaticBody.hpp"
#include "Game/IGameObject.hpp"

using namespace random_engine;

namespace game
{
	class Player : public random_engine::Object, public IGameObject
	{
		mutable Sprite sprite;
		mutable PhysicalRect physical_rect;

		bool actionIsCommited = false;
		vec2 prev_position = vec2();

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		using Callback = void (*)(Player&, float delta);
		using UpdateDirectionCallback = vec2(*)(const Player&, vec2 dir, float delta);
	private:
		Callback onClickCallback = nullptr;
		Callback onClickOnGroundCallback = nullptr;
		Callback onHoldCallback = nullptr;
		Callback onHoldOnGroundCallback = nullptr;
		UpdateDirectionCallback updateDirCallback = nullptr;

		bool onGround = false;
	public:
		Player();

		void setOnClickCallback(Callback);
		void setOnClickOnGroundCallback(Callback);
		void setOnHoldCallback(Callback);
		void setOnHoldOnGroundCallback(Callback);
		void setUpdateDirectionCallback(UpdateDirectionCallback);

		vec2 direction;
        vec2 lastOffset{ 0., 0. };
		float gravity = -50.f;
		float jumpStrength = 15.f;

		bool isOnGround() const;
		bool onClick();
		bool onClickOnGround();
		bool onHold(float delta);
		bool onHoldOnGround();
		void jump(float strength);
		void die();

		void handleEvents(const sf::Event& e) override;
		void update(float delta) override;

		void setTexture(const Texture& t);

		void collisionBegin();
		void collisionProcess(const std::vector<const StaticBody*>& bodies);
		// returns true is the cube can collide
		bool testCollisions(const std::vector<const StaticBody*>& bodies) const;
		inline const vec2& getPrevPos() const {
			return prev_position;
		}

		void setColor(const color3f& color);

		const PhysicalRect& getPhysicalRect() const;
	};
}