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

#include "Game/Level.hpp"
#include "Game/Object/SpriteObject.hpp"
#include "Game/Level/LevelLoader.hpp"

using namespace random_engine;
using namespace game;

class MyGame : public Application
{
	struct EventData
	{

	} events;

	Level level;

protected:
	void appInit() override
	{
		camera.setScale(20, 20);
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

		level.bottom.posY = -0.5f;
		level.top.posY = 7.5f;
	}
	void loadResources() override
	{
		
	}
	void startGame() override
	{
		/*level.player.setOnHoldCallback([](Player& p, float delta) {
			p.direction.y += 100.f * delta * -Math::sign(p.gravity); 
		});*/
		level.player.setOnHoldOnGroundCallback([](Player& p, float delta) {
			p.jump(16.f);
		});
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
		time_speed = 1.0f;
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
	}
	void appEnd() override
	{

	}
public:
	MyGame()
		: level(nativeCamera())
	{

	}
};

int main()
{
	//random_engine::shape_Tests();
	//return 0;

	MyGame game;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	game.res = "res";
	game.run({800, 800}, "title", sf::Style::Default, settings);

	return 0;
}