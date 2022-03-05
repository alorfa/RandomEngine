#pragma once

#include <SFML/Audio.hpp>
#include <RandomEngine/API/Graphics/Object.hpp>
#include <RandomEngine/API/Graphics/Sprite.hpp>
#include <RandomEngine/API/Math/color.hpp>
#include <RandomEngine/API/Math/CollisionFunctions.hpp>
#include "Game/Collision/StaticBody.hpp"
#include "Game/Player/GameMode.hpp"
#include "Game/Player/PlayerView.hpp"
#include "Game/Player/IconNumbers.hpp"

using namespace random_engine;

namespace game
{
	class Player : public GameObjectBase
	{
		friend struct GameMode;

		mutable PhysicalRect physical_rect, death_area;
		mutable sf::Vertex hitbox_vertices[5];
		mutable sf::Vertex death_area_vertices[5];
		mutable std::vector<sf::Vertex> path_vertices;

		sf::Sound sound;

		vec2 prev_position = vec2();

		bool actionIsCommited = false;
		bool onGround = false;

		bool is_pressed = false;

		std::unique_ptr<PlayerView> view;
	public:
		GameMode game_mode;
		IconNumbers icons;
		sf::Color main_color, side_color;

		struct CheckPoint
		{
			GameModeInfo game_mode;
			vec2 position, direction;

			inline explicit CheckPoint(const vec2& position, const vec2& direction, const GameModeInfo& gm)
				: game_mode(gm), position(position), direction(direction) {}
		};

		explicit Player();
		// sets the default state
		void reset(const CheckPoint& checkpoint);

		vec2 direction;
		bool isDead = false;

		bool isOnGround() const;
		void jump(float strength);
		void die();

		void setGameMode(const GameModeInfo& mode);

		void handleEvents(const sf::Event& e);
		void update(float delta);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void drawPath(sf::RenderTarget& target, const sf::RenderStates& states) const;

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
	};
}