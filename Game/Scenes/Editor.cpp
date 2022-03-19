#include "Editor.hpp"
#include <RandomEngine/API/GlobalData.hpp>

namespace game
{
	Editor::Editor()
		: ui(*this)
	{
		registerScene(dev_level);
		dev_level.level = &level;
		registerScene(level);
		registerScene(ui);

		level.loadBounds(res / "img/Ground.png");
		level.loadBackground(res / "img/background.png");
		dev_level.load(user / "levels/first.lvl");
	}
	void Editor::setMode(Mode mode)
	{
		switch (mode)
		{
		case Mode::Create:
			level.sound.stop();
			break;
		case Mode::Play:
			if (this->mode == Mode::Create)
				level.player.reset(Player::CheckPoint(vec2{ 0.f, 0.f }, { 10.4f, 0.f }, GameModeInfo::ball));
			level.create(dev_level);
			level.sound.play();
			break;
		case Mode::Pause:
			level.sound.pause();
			break;
		}
		this->mode = mode;
	}
	void Editor::handleEvents(const sf::Event& e)
	{
		ui.handleEvents(e);
		switch (mode)
		{
		case Mode::Create:
			dev_level.handleEvents(e);
			break;
		case Mode::Play:
			level.handleEvents(e);
			break;
		}
	}
	void Editor::update(float delta)
	{
		switch (mode)
		{
		case Mode::Create:
			dev_level.update(delta);
			break;
		case Mode::Play:
			level.update(delta);
			GlobalData::getInstance().camera.setPosition(vec2{ level.player.getPosition().x });
			break;
		}
		ui.update(delta);
	}

	void Editor::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (mode == Mode::Create)
			target.draw(dev_level, states);
		else
			target.draw(level, states);
		target.draw(ui, states);
	}

}