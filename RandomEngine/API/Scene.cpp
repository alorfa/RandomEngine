#include "Scene.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace random_engine
{
	void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const auto* scene : scenes)
			target.draw(*scene, states);
	}
	void Scene::registerScene(Scene& scene)
	{
		scene.owner = this;
		scenes.push_back(&scene);
	}
}