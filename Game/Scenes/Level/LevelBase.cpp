#include "LevelBase.hpp"
#include <RandomEngine/API/GlobalData.hpp>
#include <RandomEngine/API/Resource/TextureLoader.hpp>

namespace game
{
	void LevelBase::drawGrid(sf::RenderTarget& target, const sf::RenderStates& states) const
	{
		constexpr float OFFSET = 0.5f;
		const auto& camera = GlobalData::getInstance().camera;

		sf::Vertex line[2];
		line[0].color = line[1].color = { 0, 0, 0, 100 };
		ivec2 begin, end;
		begin.x = (int)std::floorf(camera.getPosition().x - camera.getSize().x);
		begin.y = (int)std::floorf(camera.getPosition().y - camera.getSize().y);
		end.x = (int)std::ceilf(camera.getPosition().x + camera.getSize().x);
		end.y = (int)std::ceilf(camera.getPosition().y + camera.getSize().y);

		for (int x = begin.x; x < end.x; x += 1)
		{
			line[0].position.x = line[1].position.x = (float)x - OFFSET;
			line[0].position.y = (float)begin.y - OFFSET;
			line[1].position.y = (float)end.y - OFFSET;
			target.draw(line, 2, sf::Lines, states);
		}
		for (int y = begin.y; y < end.y; y += 1)
		{
			line[0].position.y = line[1].position.y = (float)y - OFFSET;
			line[0].position.x = (float)begin.x - OFFSET;
			line[1].position.x = (float)end.x - OFFSET;
			target.draw(line, 2, sf::Lines, states);
		}
	}
	LevelBase::LevelBase()
		: bottom(Bound::Bottom), top(Bound::Top)
	{
	}

	void LevelBase::loadBounds(const std::filesystem::path& path)
	{
		const auto& texture = textureLoader.load(path);
		top.setTexture(texture);
		bottom.setTexture(texture);
	}
	void LevelBase::loadBackground(const std::filesystem::path& path)
	{
		bg.setTexture(textureLoader.load(path));
	}
}