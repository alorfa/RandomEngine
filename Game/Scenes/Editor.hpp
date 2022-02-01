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
	public:
		enum Mode
		{
			Create,
			Play,
			Pause
		};
	private:
		Mode mode;
	public:
		EditorUI ui;
		DevLevel dev_level;
		Level level;

		explicit Editor();

		inline Mode getMode() const {
			return mode;
		}
		void setMode(Mode mode);

		void handleEvents(const sf::Event& e) override;
		void update(float delta) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}