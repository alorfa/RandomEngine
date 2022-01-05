#pragma once

#include "Game/Object.hpp"
#include "Game/Player.hpp"
#include "Game/Level/Bound.hpp"
#include "Game/IGameObject.hpp"

using namespace random_engine;

namespace game
{
	class Level : public sf::Drawable, public IGameObject
	{
		float deathTime = 0.f;

		void drawGrid(sf::RenderTarget& target, const sf::RenderStates& states) const;
	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		Level();

		std::vector<Object*> objects;
		Player player;
		Bound top, bottom;
		std::vector<const StaticBody*> collisionBodies;

		void handleEvents(const sf::Event& e) override;
		void update(float delta) override;

		void loadBounds(const std::filesystem::path& path);
		void loadPlayer(const std::filesystem::path& path);
		bool load(const std::filesystem::path& path);

		~Level();
	};
}