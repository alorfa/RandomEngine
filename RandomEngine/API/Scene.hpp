#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

namespace random_engine
{
	class Scene : public sf::Drawable
	{
	protected:
		std::vector<Scene*> scenes;

		void drawScenes(sf::RenderTarget& target, const sf::RenderStates& states) const;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		virtual void handleEvents(const sf::Event& e) = 0;
		virtual void update(float delta) = 0;

		Scene* owner = nullptr;
	};
}