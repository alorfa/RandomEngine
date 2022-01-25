#pragma once

#include <RandomEngine/API/Scene.hpp>
#include "Game/Scenes/Level.hpp"
#include "Editor/EditorUI.hpp"
#include "Editor/DevLevel.hpp"

using namespace random_engine;

namespace game
{
	class Editor : public Scene
	{
		bool editor_mode = true;
	public:
		EditorUI ui;
		DevLevel dev_level;
		Level level;

		explicit Editor();

		inline bool isEditorMode() const {
			return editor_mode;
		}

		void toEditorMode();
		void toLevelMode();

		void handleEvents(const sf::Event& e) override;
		void update(float delta) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}