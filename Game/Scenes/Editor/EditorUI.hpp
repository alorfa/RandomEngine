#pragma once

#include <RandomEngine/API/UI.hpp>
#include <RandomEngine/API/UI/Button.hpp>

using namespace random_engine;

namespace game
{
	class EditorUI : public UI
	{
		Button copypaste;
		Button play, stop, reset;
	public:
		EditorUI();

		void handleEvents(const sf::Event& e) override;
		void update(float delta) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}