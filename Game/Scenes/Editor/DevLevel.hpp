#pragma once

#include "Game/Object.hpp"
#include "Game/Scenes/Level/LevelBase.hpp"
#include <map>

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
		using LevelPart = std::vector<std::unique_ptr<Object>>;
	private:
		std::map<int, std::unique_ptr<LevelPart>> parts;
	public:
		Level* level = nullptr;

		DevLevel();

		using iterator = std::vector<std::unique_ptr<Object>>::iterator;

		void addObject(std::unique_ptr<Object> obj);
		void removeObject(const iterator& obj);

		void handleEvents(const sf::Event& e) override;
		void update(float delta) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		bool load(const std::filesystem::path& path);

		inline const auto& getParts() const {
			return parts;
		}
	};
}