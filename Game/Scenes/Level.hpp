#pragma once

#include <RandomEngine/API/Scene.hpp>
#include "Game/Object.hpp"
#include "Game/Player.hpp"
#include "Game/Level/Bound.hpp"
#include "Game/Level/Background.hpp"
#include "Game/IGameObject.hpp"

using namespace random_engine;

namespace game
{
	class Level : public Scene
	{
		sf::Sound sound;

		float deathTime = 0.f;

		void drawGrid(sf::RenderTarget& target, const sf::RenderStates& states) const;

		Player::CheckPoint checkpoint;
	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		Level();

		std::vector<Object*> objects;
		Player player;
		Bound top, bottom;
		Background bg;
		std::vector<const StaticBody*> collisionBodies;

		void reset();
		void stop();

		void handleEvents(const sf::Event& e) override;
		void update(float delta) override;

		void loadBounds(const std::filesystem::path& path);
		void loadPlayer(const std::filesystem::path& path);
		void loadBackground(const std::filesystem::path& path);
		bool load(const std::filesystem::path& path);
		void sortObjects();

		~Level();
	};
}