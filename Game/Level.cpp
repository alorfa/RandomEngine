#include "Level.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include "Game/Settings.hpp"
#include "Game/Level/LevelLoader.hpp"

namespace game
{
	void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(bottom);
		target.draw(top);
		for (const auto* ptr : objects)
			target.draw(*ptr);
		target.draw(player);
	}
	Level::Level(const Camera& camera)
		: bottom(Bound::Bottom, camera), top(Bound::Top, camera)
	{
		collisionBodies.push_back(&top);
		collisionBodies.push_back(&bottom);
	}
	void Level::handleEvents(const sf::Event& e)
	{
		player.handleEvents(e);
	}
	void Level::update(float delta)
	{
		if (player.isDead)
		{
			replayTime -= delta;
		}
		if (replayTime <= 0.f)
		{
			replayTime = Settings::REPLAY_TIME;
			player.reset(Player::CheckPoint({ 0.f, 0.f }, { 0.f, 0.f }));
		}

		for (auto& obj : objects)
			obj->update(delta);
		player.update(delta);

		player.collisionBegin();
		player.collisionProcess(collisionBodies);
		if (player.testCollisions(collisionBodies))
			player.die();
	}
	void Level::loadBounds(const std::filesystem::path& path)
	{
		const auto& texture = textureLoader.load(path);
		top.setTexture(texture);
		bottom.setTexture(texture);
	}
	void Level::loadPlayer(const std::filesystem::path& path)
	{
		player.setTexture(textureLoader.load(path));
	}
	void Level::load(const std::filesystem::path& path)
	{
		std::unique_ptr<LevelState> level{ levelLoader.loadFromFile(path) };
		if (not level)
			return;
		
		objects = std::move(level->objects);
		top.posY = level->top_ground;
		bottom.posY = level->bottom_ground;
	}
	Level::~Level()
	{
		for (auto* ptr : objects)
			delete ptr;
	}
}