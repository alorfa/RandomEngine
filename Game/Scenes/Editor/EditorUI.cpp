#include "EditorUI.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <RandomEngine/API/GlobalData.hpp>
#include "Game/Scenes/Editor.hpp"
#include <RandomEngine/API/Resource/TextureLoader.hpp>
#include "Game/Scenes/Editor/DevLevel.hpp"

namespace game
{
	EditorUI::EditorUI(Editor& editor)
		: UI(Camera({0.f, 0.f}, 0.f, {10.f, 10.f})), objects(camera, editor.dev_level)
	{
		this->editor = &editor;
		registerComponent(objects);
		registerComponent(copypaste);
		registerComponent(play);
		registerComponent(stop);
		registerComponent(reset);

		const auto& res = GlobalData::getInstance().res;
		copypaste.sprite.setTexture(textureLoader.load(res / "img/ui.png"));
		play.sprite.setTexture(copypaste.sprite.getTexture());
		stop.sprite.setTexture(copypaste.sprite.getTexture());
		reset.sprite.setTexture(copypaste.sprite.getTexture());
		copypaste.sprite.setArea({0.f, 0.9f}, {0.1f, 1.f});
		play.sprite.setArea({ 0.1f, 0.9f }, { 0.2f, 1.f });
		stop.sprite.setArea({ 0.2f, 0.9f }, { 0.3f, 1.f });
		reset.sprite.setArea({ 0.3f, 0.9f }, { 0.4f, 1.f });
		camera.updateNativeSize();
		updateComponentsAlignment();

		play.onReleased = [](Button& self) {
			Editor& editor = self.owner->owner->as<Editor>();
			editor.setMode(Editor::Play);
		};
		stop.onReleased = [](Button& self) {
			Editor& editor = self.owner->owner->as<Editor>();
			editor.setMode(Editor::Pause);
		};
		reset.onReleased = [](Button& self) {
			Editor& editor = self.owner->owner->as<Editor>();
			editor.setMode(Editor::Create);
		};

		editor_comps.push_back(&play);
		editor_comps.push_back(&objects);
		editor_comps.push_back(&copypaste);

		play_comps.push_back(&stop);
		play_comps.push_back(&reset);

		pause_comps.push_back(&play);
		pause_comps.push_back(&reset);
	}
	const std::vector<UIComponent*>& EditorUI::getActiveComps() const
	{
		static std::vector<UIComponent*> def_result;
		switch (editor->getMode())
		{
		case Editor::Create:
			return editor_comps;
		case Editor::Play:
			return play_comps;
		case Editor::Pause:
			return pause_comps;
		}
		return def_result;
	}
	void EditorUI::updateComponentsAlignment()
	{
		camera.updateNativeSize();
		setCompAlignment(copypaste.sprite, UI::Right, { -1.f, 0.f });
		setCompAlignment(play.sprite, UI::Left, { 1.f, 0.f });
		setCompAlignment(stop.sprite, UI::Left, { 1.f, 0.f });
		setCompAlignment(reset.sprite, UI::Left, { 2.f, 0.f });
	}
	void EditorUI::handleEvents(const sf::Event& e)
	{
		if (e.type == sf::Event::Resized)
			updateComponentsAlignment();

		for (auto* comp : getActiveComps())
			comp->handleEvents(e);

		if (editor->getMode() != Editor::Play)
			hotkeyHandler.handleEvents(e);
	}
	void EditorUI::update(float delta)
	{
		camera.updateNativeSize();
		for (auto* comp : getActiveComps())
			comp->update(delta);
	}
	void EditorUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.setView(camera.getSFMLView()); 
		for (const auto* comp : getActiveComps())
			target.draw(*comp, states);
	}
}