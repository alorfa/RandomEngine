#include <iostream>
#include <RandomEngine/API/Application.hpp>

#include <RandomEngine/API/Math.hpp>
#include <RandomEngine/API/Graphics/VertexObject.hpp>
#include <RandomEngine/API/Graphics/Sprite.hpp>
#include <RandomEngine/API/Graphics/Shape.hpp>
#include <RandomEngine/API/System/Mouse.hpp>
#include <RandomEngine/API/System/Keyboard.hpp>
#include <RandomEngine/API/Resource/TextureLoader.hpp>
#include <RandomEngine/API/Math/Functions.hpp>

#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include <RandomEngine/API/Auxiliary/print_vectors.hpp>

#include <RandomEngine/API/Tests/ShapeTests.hpp>
#include <RandomEngine/API/UI/Button.hpp>

#include "Game/Level.hpp"
#include "Game/Object/SpriteObject.hpp"
#include "Game/Level/LevelLoader.hpp"
#include "Game/Scenes/MainMenu.hpp"

using namespace random_engine;
using namespace game;

class MyGame : public Application
{
	Level level;
	MainMenu main_menu;
protected:
	void appInit() override
	{
		camera.setSize(10, 10);
		levelLoader.setResourcesPath(res);

		level.loadBounds(res / "img/Ground.png");
		level.loadPlayer(res / "img/Cube004.png");
		level.player.setPosition(0.f, 2.f);
		level.load(res / "levels/first.json");
		
		for (const auto* ptr : level.objects)
		{
			if (ptr->collisionMode != StaticBody::None)
				level.collisionBodies.push_back(ptr);
		}
		PRINT(level.collisionBodies.size());
	}
	void loadResources() override
	{
		
	}
	void startGame() override
	{
		/*level.player.setOnClickCallback([](Player& p, float delta) {
			p.gravity = -p.gravity;
		});
		level.player.setUpdateDirectionCallback([](const Player& p, vec2 dir, float delta) {
			dir.y = dir.x * (1.f / p.getScale().x) * Math::sign(p.gravity);
			return dir;
		});
		level.player.setOnHoldCallback([](Player& p, float delta) {
			p.direction.y = -p.direction.y;
		});*/
		time_speed = 1.f;
	}
	void handleEvent(const sf::Event& e) override
	{
		if (e.type == e.MouseWheelScrolled)
		{
			if (e.mouseWheelScroll.delta > 0)
				camera.scale(0.9f, 0.9f);
			if (e.mouseWheelScroll.delta < 0)
				camera.scale(1.1f, 1.1f);
		}
		if (e.type == e.KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Down)
				level.player.scale(0.5f, 0.5f);
			if (e.key.code == sf::Keyboard::Up)
				level.player.scale(2.f, 2.f);
		}
		level.handleEvents(e);
		main_menu.handleEvents(e);
	}
	void update(float base_delta, float delta) override
	{
		level.update(delta);

		camera.setPosition(vec2(level.player.getPosition().x));
	}
	void draw(sf::RenderTarget& window) const override
	{
		window.clear({ 127, 127, 127, 255 });
		window.draw(level);
		window.draw(main_menu);
	}
	void appEnd() override
	{

	}
public:
	MyGame(GlobalData& data)
		: Application(data)
	{

	}
};

int main()
{
	GlobalData::getInstance().res = "res";
	MyGame game(GlobalData::getInstance());
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	game.run({800, 800}, "title", sf::Style::Default, settings);

	return 0;
}