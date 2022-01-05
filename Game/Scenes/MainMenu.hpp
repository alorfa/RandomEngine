#pragma once

#include <RandomEngine/API/UI.hpp>
#include <RandomEngine/API/UI/Button.hpp>

using namespace random_engine;

namespace game
{
	class MainMenu : public UI
	{
		Button left, right;
	protected:
		void draw(sf::RenderTarget&, sf::RenderStates states) const override;
	public:
		MainMenu();

		void handleEvents(const sf::Event& e);
	};
}