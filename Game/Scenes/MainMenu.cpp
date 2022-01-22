#include "MainMenu.hpp"
#include <RandomEngine/API/Resource/TextureLoader.hpp>
#include <RandomEngine/API/Application.hpp>
#include "MainScene.hpp"
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>

namespace game
{
	void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.setView(camera.getSFMLView());
		target.draw(left, states);
		target.draw(right, states);
		target.draw(center, states);
	}
	MainMenu::MainMenu()
	{
		const std::filesystem::path& res = GlobalData::getInstance().res;
		camera.setPosition(0.f, 0.f);
		camera.setSize(3.f, 3.f);
		center.setTexture(textureLoader.load(res / "img/button1.jpg"));
		center.scene = left.scene = right.scene = this;
		left.setPosition(-1.0f, 0.f);
		right.setPosition(1.0f, 0.f);
		left.setScale(0.5f, 0.5f);
		right.setScale(0.5f, 0.5f);
		left.setTexture(center.getTexture());
		right.setTexture(center.getTexture());
		center.camera = right.camera = left.camera = &camera;
		left.onClick = right.onClick = center.onClick = [](Scene& scene) {
			MainScene* mscene = dynamic_cast<MainScene*>(scene.owner);
			if (not mscene)
			{
				DEBUG("NOT A MAIN SCENE");
				return;
			}
			mscene->active_scene = &mscene->level;
			mscene->level.reset();
		};
	}
	void MainMenu::handleEvents(const sf::Event& e)
	{
		camera.updateNativeSize();

		left.handleEvents(e);
		right.handleEvents(e);
		center.handleEvents(e);
	}
	void MainMenu::update(float delta)
	{
	}
}