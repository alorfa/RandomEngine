#include "Level.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Audio.hpp>
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include "Game/Settings.hpp"
#include "Game/Scenes/Level/LevelLoader.hpp"
#include <RandomEngine/API/GlobalData.hpp>
#include <RandomEngine/API/Resource/TextureLoader.hpp>
#include <RandomEngine/API/Resource/SoundLoader.hpp>
#include "Game/Scenes/MainScene.hpp"

namespace game
{
	void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(bg);
		target.draw(bottom);
		target.draw(top);
		if (Settings::show_grid)
			drawGrid(target, states);
		for (const auto& ptr : objects)
			target.draw(*ptr, states);
		if (Settings::show_player_path)
			player.drawPath(target, states);
		target.draw(player);

		if (Settings::show_hitboxes)
		{
			for (const auto& ptr : objects)
				ptr->drawHitbox(target, states);
		}
	}
	Level::Level()
		: checkpoint({0.f, 0.f}, {10.4f, 0.f}, GameMode::cube)
	{
		collisionBodies.push_back(&top);
		collisionBodies.push_back(&bottom);

		sound.setBuffer(soundLoader.load(GlobalData::getInstance().res / "sounds/lancer.ogg"));
	}
	void Level::handleEvents(const sf::Event& e)
	{
		if (e.type == e.KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Down)
				player.scale(0.5f, 0.5f);
			if (e.key.code == sf::Keyboard::Up)
				player.scale(2.f, 2.f);
			if (e.key.code == sf::Keyboard::Escape)
			{
				auto* mscene = dynamic_cast<MainScene*>(owner->owner);
				mscene->active_scene = &mscene->main_menu;
				sound.stop();
				player.reset(checkpoint);
			}
		}
		player.handleEvents(e);
	}
	void Level::update(float delta)
	{
		if (deathTime >= Settings::REPLAY_TIME)
		{
			sound.play();
			deathTime = 0.f;
			player.reset(checkpoint);
		}
		if (player.isDead)
		{
			sound.stop();
			deathTime += delta;
			return;
		}

		for (auto& obj : objects)
		{
			obj->update(delta);
			if (obj->collisionMode == StaticBody::Touch or // use portals etc
				obj->collisionMode == StaticBody::OnClick) // run the actions of spheres before player updating
			{
				player.collisionProcess(*obj);
			}
		}
		player.update(delta);
		player.collisionBegin();
		for (const auto* body : collisionBodies)
			player.collisionProcess(*body);
		player.collisionEnd();

		for (const auto* body : collisionBodies)
		{
			if (player.testCollisions(*body))
				player.die();
		}
	}
	void Level::loadPlayer(const std::filesystem::path& path)
	{
		player.setTexture(textureLoader.load(path));
	}
	bool Level::load(const std::filesystem::path& path)
	{
		std::unique_ptr<LevelState> level{ levelLoader.loadFromFile(path) };
		if (not level)
			return false;
		
		objects = std::move(level->objects);
		top.pos = level->top_ground;
		bottom.pos = level->bottom_ground;

		sortObjects();
		return true;
	}
	void Level::create(const DevLevel& dev)
	{
		objects.clear();
		for (const auto& part : dev.getParts())
		{
			for (const auto& obj : *part.second)
			{
				objects.push_back(std::unique_ptr<Object>(obj->clone()));
			}
		}

		sortObjects();
	}
	void Level::sortObjects()
	{
		std::sort(objects.begin(), objects.end(), [](
			const std::unique_ptr<Object>& o1, const std::unique_ptr<Object>& o2) {
			return o2->getPosition().x > o1->getPosition().x;
		});

		collisionBodies.clear();
		collisionBodies.push_back(&top);
		collisionBodies.push_back(&bottom);
		for (const auto& obj : objects)
		{
			if (obj->collisionMode == StaticBody::Repulsion)
				collisionBodies.push_back(obj.get());
		}
	}
}