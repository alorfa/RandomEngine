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

#include "Game/Object/SpriteObject.hpp"
#include "Game/Scenes/Level/LevelLoader.hpp"
#include "Game/Scenes/MainScene.hpp"

using namespace random_engine;
using namespace game;

class MyGame : public Application
{
	MainScene main_scene;
protected:

	void appInit() override
	{
		camera.setSize(10, 10);
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
		try
		{
			if (e.type == e.MouseWheelScrolled)
			{
				if (e.mouseWheelScroll.delta > 0)
					camera.scale(0.9f, 0.9f);
				if (e.mouseWheelScroll.delta < 0)
					camera.scale(1.1f, 1.1f);
			}

			main_scene.handleEvents(e);
		}
		catch (AbortEventProcessing) {}
	}
	void update(float base_delta, float delta) override
	{
		main_scene.update(delta);
	}
	void draw(sf::RenderTarget& window) const override
	{
		window.clear({ 127, 127, 127, 255 });
		window.draw(main_scene);
	}
	void appEnd() override
	{

	}
public:
	explicit MyGame(GlobalData& data)
		: Application(data)
	{

	}
};

int main()
{
	GlobalData::getInstance().res = "res";
	GlobalData::getInstance().user = "user";
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	GlobalData::getInstance().window.create({ 800, 800 }, "title", sf::Style::Default, settings);
	MyGame game(GlobalData::getInstance());
	game.run();

	return 0;
}