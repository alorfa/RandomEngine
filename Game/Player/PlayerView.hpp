#pragma once

#include <memory>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "Game/Player/IconNumbers.hpp"

using namespace random_engine;

namespace game
{
	class Player;

	class PlayerView : public sf::Drawable
	{
	public:
		enum Type
		{
			Cube, Ship, Ball
		};
	private:
		Type _type;
	public:
		PlayerView(Type type);
		inline Type type() const {
			return _type;
		}

		virtual void setMainColor(const sf::Color& color) = 0;
		virtual void setSideColor(const sf::Color& color) = 0;

		virtual void update(float delta) = 0;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		static std::unique_ptr<PlayerView> createView(PlayerView::Type type,
			const sf::Color& main, const sf::Color& side, 
			const IconNumbers& icons, const Player& player);
	};
}