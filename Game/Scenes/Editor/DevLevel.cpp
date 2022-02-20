#include "DevLevel.hpp"
#include "Game/Scenes/Level/BinaryLevelLoader.hpp"
#include <RandomEngine/API/GlobalData.hpp>
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include "Game/Scenes/Level.hpp"
#include "Game/Settings.hpp"

namespace game
{
	void DevLevel::removeSelectedObjectsInPart(LevelPart& part)
	{
		part.remove_if([](const std::unique_ptr<Object>& obj) {
			return obj->is_selected;
		});
	}
	DevLevel::DevLevel()
	{
	}
	void DevLevel::addObject(std::unique_ptr<Object> obj)
	{
		const int posX = int(obj->getPosition().x * 0.1);
		std::unique_ptr<LevelPart>& part = parts[posX];
		if (not part)
			part = std::make_unique<LevelPart>();
		parts[posX]->push_front(std::move(obj));
	}
	void DevLevel::removeSelectedObjects()
	{
		for (auto& part : parts)
		{
			removeSelectedObjectsInPart(*part.second);
		}
	}
	void DevLevel::handleEvents(const sf::Event& e)
	{

	}
	void DevLevel::update(float delta)
	{
	}
	void DevLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(level->bg);
		target.draw(level->top);
		target.draw(level->bottom);
		if (Settings::show_grid)
			level->drawGrid(target, states);
		for (const auto& part : parts)
		{
			for (const auto& obj : *part.second)
			{
				target.draw(*obj, states);
			}
		}
		if (Settings::show_hitboxes)
		{
			for (const auto& part : parts)
			{
				for (const auto& obj : *part.second)
				{
					obj->drawHitbox(target, states);
				}
			}
		}
		level->player.drawPath(target, states);
	}
	bool DevLevel::load(const std::filesystem::path& path)
	{
		const std::unique_ptr<LevelState> levelState(binaryLevelLoader.loadFromFile(path));
		if (not levelState)
			return false;

		for (auto& obj : levelState->objects)
		{
			addObject(std::move(obj));
		}
		level->bottom.pos = levelState->bottom_ground;
		level->top.pos = levelState->top_ground;

		return true;
	}
}