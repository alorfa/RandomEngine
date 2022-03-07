#pragma once

#include <SFML/Audio.hpp>
#include <RandomEngine/API/Graphics/Sprite.hpp>
#include <RandomEngine/API/Math/color.hpp>
#include <RandomEngine/API/Math/CollisionFunctions.hpp>
#include "Game/Collision/StaticBody.hpp"
#include "Game/Player/GameMode.hpp"
#include "Game/Player/PlayerView.hpp"
#include "Game/Player/IconNumbers.hpp"
#include "Game/Collision/DynamicBody.hpp"

using namespace random_engine;

namespace game
{
	class Player : public DynamicBody
	{
		friend struct GameMode;
		friend class DynamicBody;

		mutable std::vector<sf::Vertex> path_vertices;

		sf::Sound sound;

		bool actionIsCommited = false;

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

		bool isDead = false;

		void jump(float strength);
		void die();

		void setGameMode(const GameModeInfo& mode);

		void handleEvents(const sf::Event& e);
		void update(float delta);
		void updateView(float delta);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void drawPath(sf::RenderTarget& target, const sf::RenderStates& states) const;
	};
}