#include "MainMenu.hpp"
#include <RandomEngine/API/Resource/TextureLoader.hpp>
#include <RandomEngine/API/Application.hpp>

namespace game
{
	void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.setView(camera.getSFMLView());
		target.draw(left, states);
		target.draw(right, states);
	}
	MainMenu::MainMenu()
	{
		const std::filesystem::path& res = GlobalData::getInstance().res;
		camera.setSize(3.f, 3.f);
		left.setPosition(-0.5f, 0.5f);
		right.setPosition(0.5f, 0.5f);
		left.setTexture(textureLoader.load(res / "img/button1.jpg"));
		right.setTexture(left.getTexture());
	}
	void MainMenu::handleEvents(const sf::Event& e)
	{
		left.handleEvents(e);
		right.handleEvents(e);
	}
}