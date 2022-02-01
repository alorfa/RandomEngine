#pragma once

#include "Game/Object.hpp"
#include "Game/Scenes/Level/LevelBase.hpp"
#include <map>
#include <forward_list>

using namespace random_engine;

namespace std::filesystem
{
	class path;
}

namespace game
{
	class Level;

	class DevLevel : public Scene
	{
	public:
		template <typename T>
		using container = std::forward_list<T>;

		using LevelPart = container<std::unique_ptr<Object>>;
	private:
		std::map<int, std::unique_ptr<LevelPart>> parts;

		void removeSelectedObjectsInPart(LevelPart& part);
	public:
		Level* level = nullptr;

		DevLevel();

		using iterator = container<std::unique_ptr<Object>>::iterator;

		void addObject(std::unique_ptr<Object> obj);
		void removeSelectedObjects();

		void handleEvents(const sf::Event& e) override;
		void update(float delta) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		bool load(const std::filesystem::path& path);

		inline const auto& getParts() const {
			return parts;
		}
	};
}