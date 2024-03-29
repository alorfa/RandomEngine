#pragma once

#include <RandomEngine/API/Scene.hpp>
#include "Level.hpp"
#include "MainMenu.hpp"
#include "Editor.hpp"

using namespace random_engine;

namespace game
{
	class MainScene : public Scene
	{
	public:
		MainScene();

		Editor editor;
		MainMenu main_menu;
		Scene* active_scene = nullptr;

		void handleEvents(const sf::Event& e) override;
		void update(float delta) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}