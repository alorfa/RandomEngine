#include "Editor.hpp"
#include <RandomEngine/API/GlobalData.hpp>

namespace game
{
	Editor::Editor()
	{
		registerScene(dev_level);
		dev_level.level = &level;
		registerScene(level);
		registerScene(ui);

		const auto& res = GlobalData::getInstance().res;
		const auto& user = GlobalData::getInstance().user;
		level.loadBounds(res / "img/Ground.png");
		level.loadBackground(res / "img/background.png");
		level.loadPlayer(res / "img/Cube004.png");
		dev_level.load(user / "levels/first.json");
	}
	void Editor::toEditorMode()
	{
		editor_mode = true;
		level.sound.pause();
	}
	void Editor::toLevelMode()
	{
		editor_mode = false;
		level.create(dev_level);
		level.sound.play();
	}
	void Editor::handleEvents(const sf::Event& e)
	{
		ui.handleEvents(e);
		if (editor_mode)
			dev_level.handleEvents(e);
		else
			level.handleEvents(e);
	}
	void Editor::update(float delta)
	{
		if (editor_mode)
		{
			dev_level.update(delta);
		}
		else
		{
			level.update(delta);
			GlobalData::getInstance().camera.setPosition(vec2{ level.player.getPosition().x });
		}
		ui.update(delta);
	}

	void Editor::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (not editor_mode)
			target.draw(level, states);
		if (editor_mode)
			target.draw(dev_level, states);
		target.draw(ui, states);
	}

}