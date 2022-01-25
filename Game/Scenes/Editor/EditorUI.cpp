#include "EditorUI.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <RandomEngine/API/GlobalData.hpp>
#include "Game/Scenes/Editor.hpp"
#include <RandomEngine/API/Resource/TextureLoader.hpp>

namespace game
{
	EditorUI::EditorUI()
	{
		registerComponent(copypaste);
		registerComponent(play);
		registerComponent(stop);
		registerComponent(reset);

		const auto& res = GlobalData::getInstance().res;
		copypaste.setTexture(textureLoader.load(res / "img/ui.png"));
		play.setTexture(copypaste.getTexture());
		stop.setTexture(copypaste.getTexture());
		reset.setTexture(copypaste.getTexture());
		copypaste.setArea({0.f, 0.9f}, {0.1f, 1.f});
		play.setArea({ 0.1f, 0.9f }, { 0.2f, 1.f });
		stop.setArea({ 0.2f, 0.9f }, { 0.3f, 1.f });
		reset.setArea({ 0.3f, 0.9f }, { 0.4f, 1.f });
		copypaste.setPosition(4.f, 0.f);
		play.setPosition(-4.f, 0.f);
		stop.setPosition(-4.f, 0.f);
		reset.setPosition(-3.f, 0.f);

		play.onClick = [](Scene& scene) {
			Editor& editor = dynamic_cast<Editor&>(*scene.owner);
			editor.toLevelMode();
		};
		stop.onClick = [](Scene& scene) {
			Editor& editor = dynamic_cast<Editor&>(*scene.owner);
			editor.toEditorMode();
		};
		reset.onClick = [](Scene& scene) {
			Editor& editor = dynamic_cast<Editor&>(*scene.owner);
			editor.toEditorMode();
			editor.level.sound.stop();
			editor.level.player.reset(
				Player::CheckPoint(vec2{ 0.f, 0.f }, { 10.4f, 0.f }, GameMode::cube));
		};

		camera.setPosition(0.f, 0.f);
		camera.setSize(10.f, 10.f);
	}
	void EditorUI::handleEvents(const sf::Event& e)
	{
		copypaste.handleEvents(e);
		const Editor& editor = dynamic_cast<Editor&>(*owner);
		if (editor.isEditorMode())
		{
			play.handleEvents(e);
		}
		else
		{
			stop.handleEvents(e);
			reset.handleEvents(e);
		}
	
	}
	void EditorUI::update(float delta)
	{
		copypaste.update(delta);
		const Editor& editor = dynamic_cast<Editor&>(*owner);
		if (editor.isEditorMode()) {
			play.update(delta);
		}
		else {
			stop.update(delta);
			reset.update(delta);
		}
		camera.updateNativeSize();
	}
	void EditorUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.setView(camera.getSFMLView()); 
		target.draw(copypaste, states);
		const Editor& editor = dynamic_cast<Editor&>(*owner);
		if (editor.isEditorMode()) {
			target.draw(play, states);
		}
		else {
			target.draw(stop, states);
			target.draw(reset);
		}
	}
}