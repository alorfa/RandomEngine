#include "ObjectsMenu.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <RandomEngine/API/Resource/TextureLoader.hpp>
#include <RandomEngine/API/GlobalData.hpp>
#include <RandomEngine/API/System/Mouse.hpp>
#include <RandomEngine/API/Graphics/Shape.hpp>
#include "Game/Scenes/Editor/DevLevel.hpp"
#include "Game/Object.hpp"
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include <RandomEngine/API/Auxiliary/print_vectors.hpp>
#include "Game/Settings.hpp"
#include "Game/Scenes/Level/BinaryLevelLoader.hpp"
#include "Game/Scenes/Level.hpp"
#include "Game/Object/SpriteObjectBuilder.hpp"

namespace
{
	const Rect hitbox({ -0.5f, -0.5f }, { 0.5f, 0.5f });
}

namespace game
{
	ObjectsMenu::ObjectsMenu(const Camera& camera, DevLevel& devLevel)
	{
		for (auto& vert : select_vertices)
			vert.color = sf::Color::Green;

		dev_level = &devLevel;
		this->camera = &camera;
		registerComponent(tabs);
		registerComponent(remove_btn);

		updateComponentsAlignment();
		remove_btn.sprite.setTexture(textureLoader.load(res / "img/ui.png"));
		remove_btn.sprite.setArea({ 0.4f, 0.9f }, { 0.5f, 1.f });
		remove_btn.onReleased = [](Button& button) {
			auto& objects = button.owner->as<ObjectsMenu>();
			objects.removeSelectedObjects();
		};

		Button button;
		button.sprite.setTexture(textureLoader.load(res / "img/objects.png"));
		button.sprite.setArea({ 0.f, 0.9f }, { 0.1f, 1.f });

		Tabs::ComponentsList blocks;
		auto component = std::make_unique<SelectableButton>();
		component->select_color = sf::Color(127, 127, 127, 255);
		component->sprite.setTexture(textureLoader.load(res / "img/objects.png"));
		component->sprite.setArea({ 0.f, 0.9f }, { 0.1f, 1.f });
		component->onReleased = [this](Button& button) {
			setActiveObject(button.as<SelectableButton>(),
				spriteObjectBuilder.build(1));
		};
		blocks.push_back(std::make_unique<SelectableButton>(*component));
		component->sprite.setArea({ 0.1f, 0.9f }, { 0.2f, 1.f });
		component->onReleased = [this](Button& button) {
			setActiveObject(button.as<SelectableButton>(),
				spriteObjectBuilder.build(2));
		};
		blocks.push_back(std::make_unique<SelectableButton>(*component));

		auto tab = std::make_unique<Tabs::Tab>();
		tab->tab = button;
		tab->comps = std::move(blocks);
		tab->name = "blocks";

		tabs.setTab(std::move(tab));

		button.sprite.setArea({ 0.2f, 0.9f }, { 0.3f, 1.f });

		blocks.clear();
		component->sprite.setArea({ 0.2f, 0.9f }, { 0.3f, 1.f });
		component->onReleased = [this](Button& button) {
			setActiveObject(button.as<SelectableButton>(),
				spriteObjectBuilder.build(3));
		};
		blocks.push_back(std::make_unique<SelectableButton>(*component));
		component->sprite.setArea({ 0.3f, 0.9f }, { 0.4f, 1.f });
		component->onReleased = [this](Button& button) {
			setActiveObject(button.as<SelectableButton>(), 
				spriteObjectBuilder.build(4));
		};
		blocks.push_back(std::make_unique<SelectableButton>(*component));
		component->sprite.setArea({ 0.4f, 0.9f }, { 0.5f, 1.f });
		component->onReleased = [this](Button& button) {
			setActiveObject(button.as<SelectableButton>(),
				spriteObjectBuilder.build(5));
		};
		blocks.push_back(std::make_unique<SelectableButton>(*component));

		tab = std::make_unique<Tabs::Tab>();
		tab->tab = button;
		tab->comps = std::move(blocks);
		tab->name = "spikes";

		tabs.setTab(std::move(tab));

		button.sprite.setTexture(textureLoader.load(res / "img/portals.png"));
		button.sprite.setScale(0.33f, 1.f);
		button.sprite.setArea({ 0.f, 0.f }, { 0.1f, 1.f });

		blocks.clear();
		component->sprite.setScale(0.33f, 1.f);
		component->sprite.setTexture(textureLoader.load(res / "img/portals.png"));
		component->sprite.setArea({ 0.f, 0.f }, { 0.1f, 1.f });
		component->onReleased = [this](Button& button) {
			setActiveObject(button.as<SelectableButton>(),
				spriteObjectBuilder.build(101));
		};
		blocks.push_back(std::make_unique<SelectableButton>(*component));

		component->sprite.setArea({ 0.1f, 0.f }, { 0.2f, 1.f });
		component->onReleased = [this](Button& button) {
			setActiveObject(button.as<SelectableButton>(),
				spriteObjectBuilder.build(102));
		};
		blocks.push_back(std::make_unique<SelectableButton>(*component));

		tab = std::make_unique<Tabs::Tab>();
		tab->tab = button;
		tab->comps = std::move(blocks);
		tab->name = "portals";

		tabs.setTab(std::move(tab));

		tabs.setActiveTab("spikes");

		updateComponentsAlignment();
	}

	void ObjectsMenu::setActiveObject(SelectableButton& button, std::unique_ptr<Object> obj)
	{
		if (active_button == &button)
		{
			active_button->deselect();
			active_button = nullptr;
			object = nullptr;
			return;
		}
		if (active_button)
			active_button->deselect();
		active_button = &button;
		active_button->select();
		object = std::move(obj);
	}

	void ObjectsMenu::selectObjects(const Rect& hitbox)
	{
		PhysicalRect phys_rect;
		phys_rect.min = hitbox.min;
		phys_rect.max = hitbox.max;
		for (const auto& parts : dev_level->getParts())
		{
			for (const auto& obj : *parts.second)
			{
				if (obj->touches(phys_rect))
				{
					obj->is_selected = true;
					selected_objects.push_back(obj.get());
				}
			}
		}
	}

	void ObjectsMenu::deselectObjects()
	{
		for (auto& obj : selected_objects)
			obj->is_selected = false;
		selected_objects.clear();
	}

	void ObjectsMenu::removeSelectedObjects()
	{
		dev_level->removeSelectedObjects();

		selected_objects.clear();
	}

	void ObjectsMenu::updateComponentsAlignment()
	{
		for (size_t i = 0; i < tabs.getTabs().size(); ++i)
		{
			auto& tab = tabs.getTabs()[i];
			setCompAlignment(tab->tab.sprite, UI::Bottom, { (float)i, 2.f });
			for (size_t j = 0; j < tab->comps.size(); ++j)
			{
				auto& comp = tab->comps[j];
				setCompAlignment(comp->as<Button>().sprite, UI::Bottom, { (float)j, 1.f });
			}
		}
		setCompAlignment(remove_btn.sprite, UI::Left | UI::Top, { 1.f, -1.f });
	}

	void ObjectsMenu::handleEvents(const sf::Event& e)
	{
		if (e.type == sf::Event::KeyPressed and e.key.code == sf::Keyboard::S)
		{
			binaryLevelLoader.saveToFile("user/levels/first.lvl", *dev_level);
		}

		for (auto& comp : comps)
			comp->handleEvents(e);

		switch (e.type)
		{
		case sf::Event::MouseButtonPressed:
			switch (e.mouseButton.button)
			{
			case sf::Mouse::Left:
				left_is_pressed = true;
				break;
			case sf::Mouse::Right:
				show_rect = true;
				select_begin = Mouse::getPosition();
				break;
			}
			break;
		case sf::Event::MouseButtonReleased:
			switch (e.mouseButton.button)
			{
			case sf::Mouse::Right:
				show_rect = false;
				deselectObjects();
				selectObjects(select_rect);
				break;
			case sf::Mouse::Left:
				if (object and object_time < Settings::max_object_time)
				{
					vec2 pos = Mouse::getPosition();
					pos.x = std::roundf(pos.x);
					pos.y = std::roundf(pos.y);

					auto copy = object->clone();
					copy->setPosition(pos);
					dev_level->addObject(std::move(copy));
				}
				left_is_pressed = false;
				object_time = 0.f;
				break;
			}
			break;
		case sf::Event::MouseMoved:
			if (left_is_pressed)
			{
				vec2 offset{ (float)e.mouseMove.x, (float)e.mouseMove.y };
				object_time += offset.length() * 0.00005f;
			}
			break;
		}
	}
	void ObjectsMenu::update(float delta)
	{
		if (left_is_pressed)
			object_time += delta;

		if (show_rect)
		{
			select_end = Mouse::getPosition();

			select_rect.min.x = std::min(select_begin.x, select_end.x);
			select_rect.max.x = std::max(select_begin.x, select_end.x);
			select_rect.min.y = std::min(select_begin.y, select_end.y);
			select_rect.max.y = std::max(select_begin.y, select_end.y);
		}
		for (auto& comp : comps)
			comp->update(delta);
	}
	void ObjectsMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.setView(GlobalData::getInstance().camera.getSFMLView());
		if (show_rect)
		{
			Shape::createRectangle(select_rect, select_vertices);
			target.draw(select_vertices, 5, sf::LineStrip, states);
		}
		target.setView(camera->getSFMLView());
		for (auto& comp : comps)
			target.draw(*comp, states);
	}
}