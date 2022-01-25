#include "MainScene.hpp"
#include <RandomEngine/API/GlobalData.hpp>
#include "RandomEngine/API/GlobalData.hpp"
#include "RandomEngine/API/Auxiliary/DEBUG.hpp"

namespace game
{
	MainScene::MainScene()
	{
		registerScene(main_menu);
		registerScene(editor);

		active_scene = &main_menu;
	}
	void MainScene::handleEvents(const sf::Event& e)
	{
		active_scene->handleEvents(e);
	}
	void MainScene::update(float delta)
	{
		active_scene->update(delta);
	}
	void MainScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(*active_scene, states);
	}
}