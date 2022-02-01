#pragma once

#include <RandomEngine/API/UI.hpp>
#include <RandomEngine/API/UI/Button.hpp>
#include "ObjectsMenu.hpp"
#include "HotkeyHandler.hpp"

using namespace random_engine;

namespace game
{
	class Editor;

	class EditorUI : public UI
	{
	public:
		Editor* editor = nullptr;
	private:
		Button copypaste;
		Button play, stop, reset;

		ObjectsMenu objects;

		HotkeyHandler hotkeyHandler;

		std::vector<UIComponent*> editor_comps, play_comps, pause_comps;
	public:
		EditorUI(Editor& editor);

		const std::vector<UIComponent*>& getActiveComps() const;

		void updateComponentsAlignment() override;
		void handleEvents(const sf::Event& e) override;
		void update(float delta) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}