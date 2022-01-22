#include "Level.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include "Game/Settings.hpp"
#include "Game/Level/LevelLoader.hpp"
#include <RandomEngine/API/GlobalData.hpp>

#include <SFML/Audio.hpp>
#include <RandomEngine/API/Resource/SoundLoader.hpp>
#include "Game/Scenes/MainScene.hpp"

namespace game
{
	void Level::drawGrid(sf::RenderTarget& target, const sf::RenderStates& states) const
	{
		constexpr float OFFSET = 0.5f;
		const auto& camera = GlobalData::getInstance().camera;

		sf::Vertex line[2];
		line[0].color = line[1].color = { 0, 0, 0, 100 };
		ivec2 begin, end;
		begin.x = (int)std::floorf(camera.getPosition().x - camera.getSize().x);
		begin.y = (int)std::floorf(camera.getPosition().y - camera.getSize().y);
		end.x = (int)std::ceilf(camera.getPosition().x + camera.getSize().x);
		end.y = (int)std::ceilf(camera.getPosition().y + camera.getSize().y);

		for (int x = begin.x; x < end.x; x += 1)
		{
			line[0].position.x = line[1].position.x = (float)x - OFFSET;
			line[0].position.y = (float)begin.y - OFFSET;
			line[1].position.y = (float)end.y - OFFSET;
			target.draw(line, 2, sf::Lines, states);
		}
		for (int y = begin.y; y < end.y; y += 1)
		{
			line[0].position.y = line[1].position.y = (float)y - OFFSET;
			line[0].position.x = (float)begin.x - OFFSET;
			line[1].position.x = (float)end.x - OFFSET;
			target.draw(line, 2, sf::Lines, states);
		}
	}
	void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(bg);
		target.draw(bottom);
		target.draw(top);
		if (Settings::show_grid)
			drawGrid(target, states);
		for (const auto* ptr : objects)
			target.draw(*ptr);
		target.draw(player);
	}
	Level::Level()
		: bottom(Bound::Bottom), top(Bound::Top), checkpoint({0.f, 0.f}, {10.4f, 0.f}, GameMode::cube)
	{
		collisionBodies.push_back(&top);
		collisionBodies.push_back(&bottom);

		sound.setBuffer(soundLoader.load(GlobalData::getInstance().res/"sounds/lancer.ogg"));
	}
	void Level::reset()
	{
		sound.play();
	}
	void Level::stop()
	{
		sound.stop();
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
				auto* mscene = dynamic_cast<MainScene*>(owner);
				mscene->active_scene = &mscene->main_menu;
				stop();
				player.reset(checkpoint);
			}
		}
		player.handleEvents(e);
	}
	void Level::update(float delta)
	{
		if (deathTime >= Settings::REPLAY_TIME)
		{
			reset();
			deathTime = 0.f;
			player.reset(checkpoint);
		}
		if (player.isDead)
		{
			stop();
			deathTime += delta;
			return;
		}

		for (auto* obj : objects)
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
	void Level::loadBackground(const std::filesystem::path& path)
	{
		bg.setTexture(textureLoader.load(path));
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
	void Level::sortObjects()
	{
		std::sort(objects.begin(), objects.end(), [](const Object* o1, const Object* o2) {
			return o2->getPosition().x > o1->getPosition().x;
		});

		for (const auto* ptr : objects)
		{
			DEBUG(ptr->getPosition().x);
			if (ptr->collisionMode != StaticBody::None)
				collisionBodies.push_back(ptr);
		}
	}
	Level::~Level()
	{
		for (auto* ptr : objects)
			delete ptr;
	}
}