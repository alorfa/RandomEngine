#include "MainScene.hpp"
#include <RandomEngine/API/GlobalData.hpp>
#include "RandomEngine/API/GlobalData.hpp"
#include "RandomEngine/API/Auxiliary/DEBUG.hpp"

namespace game
{
	MainScene::MainScene()
	{
		level.owner = this;
		main_menu.owner = this;

		active_scene = &main_menu;

		const auto& res = GlobalData::getInstance().res;

		level.loadBounds(res / "img/Ground.png");
		level.loadPlayer(res / "img/Cube004.png");
		level.loadBackground(res / "img/background.png");
		level.load(res / "levels/first.json");

		PRINT(level.collisionBodies.size());
	}
	void MainScene::handleEvents(const sf::Event& e)
	{
		active_scene->handleEvents(e);
	}
	void MainScene::update(float delta)
	{
		active_scene->update(delta);
		GlobalData::getInstance().camera.setPosition(vec2(level.player.getPosition().x));
	}
	void MainScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(*active_scene, states);
	}
}