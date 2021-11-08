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

		std::vector<vec2> touchVectors;
	public:
		Player();

		void setOnClickCallback(Callback);
		void setOnClickOnGroundCallback(Callback);
		void setOnHoldCallback(Callback);
		void setOnHoldOnGroundCallback(Callback);
		void setUpdateDirectionCallback(UpdateDirectionCallback);

		vec2 direction;
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

		void setColor(const color3f& color);
	};
}