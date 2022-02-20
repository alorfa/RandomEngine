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
		camera.setPosition(0.f, 0.f);
		camera.setSize(3.f, 3.f);
		center.sprite.setTexture(textureLoader.load(res / "img/button1.jpg"));
		center.owner = left.owner = right.owner = this;
		left.sprite.setPosition(-1.0f, 0.f);
		right.sprite.setPosition(1.0f, 0.f);
		left.sprite.setScale(0.5f, 0.5f);
		right.sprite.setScale(0.5f, 0.5f);
		left.sprite.setTexture(center.sprite.getTexture());
		right.sprite.setTexture(center.sprite.getTexture());
		center.camera = right.camera = left.camera = &camera;
		left.onReleased = right.onReleased = center.onReleased = [](Button& self) {
			auto& mscene = self.owner->owner->as<MainScene>();
			mscene.active_scene = &mscene.editor;
		};
	}
	void MainMenu::updateComponentsAlignment()
	{
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