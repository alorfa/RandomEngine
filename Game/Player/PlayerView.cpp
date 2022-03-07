#include "PlayerView.hpp"
#include <RandomEngine/API/Math/CollisionFunctions.hpp>
#include <RandomEngine/API/Resource/TextureLoader.hpp>
#include <RandomEngine/API/GlobalData.hpp>
#include "Game/Player.hpp"

#include "PlayerView/CubeView.hpp"
#include "PlayerView/ShipView.hpp"

namespace game
{
	PlayerView::PlayerView(Type type)
		: _type(type) {}

	std::unique_ptr<PlayerView> PlayerView::createView(PlayerView::Type type,
		const sf::Color& main, const sf::Color& side, 
		const IconNumbers& icons, const Player& player)
	{
		switch (type)
		{
		case Type::Cube:
			return std::make_unique<CubeView>(main, side, icons.cube, player);
		case Type::Ship:
			return std::make_unique<ShipView>(main, side, icons.ship, icons.cube, player);
		}
		return std::make_unique<CubeView>(main, side, icons.cube, player);
		
	}
}