#pragma once

#include <RandomEngine/API/Scene.hpp>
#include "Game/Object.hpp"
#include "Game/Player.hpp"
#include "Level/LevelBase.hpp"

using namespace random_engine;

namespace boost::serialization
{
	class access;
}

namespace game
{
	class DevLevel;

	class Level : public LevelBase
	{
		float deathTime = 0.f;
	public:
		Level();

		sf::Sound sound;

		Player player;
		Player::CheckPoint checkpoint;
		std::vector<std::unique_ptr<Object>> objects;
		std::vector<const StaticBody*> collisionBodies;

		void handleEvents(const sf::Event& e) override;
		void update(float delta) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		bool load(const std::filesystem::path& path);
		void create(const DevLevel& dev);
		void sortObjects();
	};
}