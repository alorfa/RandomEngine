#include "Level.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>

namespace game
{
	void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(bottom);
		target.draw(top);
		for (const auto* ptr : objects)
			target.draw(*ptr);
		target.draw(player);
	}
	Level::Level(const Camera& camera)
		: bottom(Bound::Bottom, camera), top(Bound::Top, camera)
	{
		collisionBodies.push_back(&top);
		collisionBodies.push_back(&bottom);
	}
	void Level::handleEvents(const sf::Event& e)
	{
		player.handleEvents(e);
	}
	void Level::update(float delta)
	{
		player.update(delta);
		for (auto& obj : objects)
			obj->update(delta);

		player.collisionBegin();
        if(player.collisionProcess(collisionBodies) 
            && player.testCollisions(collisionBodies))
            player.die();
	}
	void Level::loadBounds(const std::filesystem::path& path)
	{
		const auto& texture = textureLoader.load(path);
		top.setTexture(texture);
		bottom.setTexture(texture);
	}
	void Level::loadPlayer(const std::filesystem::path& path)
	{
		player.setTexture(textureLoader.load(path));
	}
	Level::~Level()
	{
		for (auto* ptr : objects)
			delete ptr;
	}
}