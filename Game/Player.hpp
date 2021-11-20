#pragma once

#include <RandomEngine/API/Graphics/Object.hpp>
#include <RandomEngine/API/Graphics/Sprite.hpp>
#include <RandomEngine/API/Math/color.hpp>
#include "Game/Collision/StaticBody.hpp"
#include "Game/IGameObject.hpp"

using namespace random_engine;

namespace game
{
	class Player : public random_engine::Object, public IGameObject
	{
		mutable Sprite sprite;

		bool actionIsCommited = false;
		Vec2 prev_position = Vec2();

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		using Callback = void (*)(Player&, float delta);
		using UpdateDirectionCallback = Vec2(*)(const Player&, Vec2 dir, float delta);
	private:
		Callback onClickCallback = nullptr;
		Callback onClickOnGroundCallback = nullptr;
		Callback onHoldCallback = nullptr;
		Callback onHoldOnGroundCallback = nullptr;
		UpdateDirectionCallback updateDirCallback = nullptr;

		std::vector<Vec2> touchVectors;
	public:
		Player();

		void setOnClickCallback(Callback);
		void setOnClickOnGroundCallback(Callback);
		void setOnHoldCallback(Callback);
		void setOnHoldOnGroundCallback(Callback);
		void setUpdateDirectionCallback(UpdateDirectionCallback);

		Vec2 direction;
		float gravity = -50.f;
		float jumpStrength = 15.f;

		bool isOnGround() const;
		bool onClick();
		bool onClickOnGround();
		bool onHold(float delta);
		bool onHoldOnGround();
		void jump(float strength);

		void handleEvents(const sf::Event& e) override;
		void update(float delta) override;

		void setTexture(const Texture& t);

		void collisionProcess(const std::vector<const StaticBody*>& bodies);
		inline const Vec2& getPrevPos() const {
			return prev_position;
		}

		void setColor(const color3f& color);
	};
}