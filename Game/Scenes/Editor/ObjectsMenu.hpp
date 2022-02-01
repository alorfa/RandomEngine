#pragma once

#include <RandomEngine/API/UI/Tabs.hpp>
#include <RandomEngine/API/UI.hpp>
#include <RandomEngine/API/UI/SelectableButton.hpp>
#include "Game/Object.hpp"

using namespace random_engine;

namespace game
{
	class DevLevel;

	class ObjectsMenu : public UIComponent
	{
		SelectableButton* active_button = nullptr;

		mutable sf::Vertex select_vertices[5];
		Rect select_rect;
		vec2 select_begin, select_end;
		bool show_rect = false;
		std::vector<Object*> selected_objects;

		float object_time = 0.f;
		bool left_is_pressed = false;
	public:
		Tabs tabs;
		Button remove_btn;

		DevLevel* dev_level = nullptr;
		std::unique_ptr<game::Object> object;

		ObjectsMenu(const Camera& camera, DevLevel& devLevel);

		void setActiveObject(SelectableButton& button, std::unique_ptr<Object> obj);

		void selectObjects(const Rect& hitbox);
		void deselectObjects();
		void removeSelectedObjects();

		void updateComponentsAlignment() override;
		void handleEvents(const sf::Event& e) override;
		void update(float delta) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}