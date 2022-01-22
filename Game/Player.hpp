#pragma once

#include <SFML/Audio.hpp>
#include <RandomEngine/API/Graphics/Object.hpp>
#include <RandomEngine/API/Graphics/Sprite.hpp>
#include <RandomEngine/API/Math/color.hpp>
#include <RandomEngine/API/Math/CollisionFunctions.hpp>
#include "Game/Collision/StaticBody.hpp"
#include "Game/IGameObject.hpp"
#include "Game/Player/GameMode.hpp"

using namespace random_engine;

namespace game
{
	class Player : public random_engine::Object, public IGameObject
	{
		friend struct GameMode;

		mutable Sprite sprite;
		mutable PhysicalRect physical_rect, death_area;
		mutable sf::Vertex hitbox_vertices[5];
		mutable sf::Vertex death_area_vertices[5];
		mutable std::vector<sf::Vertex> path_vertices;

		sf::Sound sound;

		vec2 prev_position = vec2();

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		bool actionIsCommited = false;
		bool onGround = false;

		bool is_pressed = false;
	public:
		struct CheckPoint
		{
			GameMode game_mode;
			vec2 position, direction;

			inline explicit CheckPoint(const vec2& position, const vec2& direction, const GameMode& gm)
				: game_mode(gm), position(position), direction(direction) {}
		};

		explicit Player();
		// sets the default state
		void reset(const CheckPoint& checkpoint);

		GameMode game_mode;
		vec2 direction;
		bool isDead = false;

		bool isOnGround() const;
		void jump(float strength);
		void die();

		void handleEvents(const sf::Event& e) override;
		void update(float delta) override;

		void setTexture(const Texture& t);

		void collisionBegin();
		void collisionProcess(const StaticBody& bodies);
		// returns true is the cube can collide
		bool testCollisions(const StaticBody& bodies) const;
		inline const vec2& getPrevPos() const {
			return prev_position;
		}
		void collisionEnd();

		void setColor(const color3f& color);

		const PhysicalRect& getPhysicalRect() const;
		const PhysicalRect& getDeathArea() const;
	};
}