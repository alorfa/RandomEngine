#include "ObjectActions.hpp"
#include "Game/Player.hpp"

namespace game
{
	void ObjectActions::die(Player& p)
	{
		p.die();
	}
	void ObjectActions::normalJump(Player& p)
	{
		p.jump(1.f);
	}
	void ObjectActions::littleJump(Player& p)
	{
		p.jump(0.6f);
	}
	void ObjectActions::toCube(Player& p)
	{
		p.game_mode = GameMode::cube;
	}
	void ObjectActions::toShip(Player& p)
	{
		p.game_mode = GameMode::ship;
	}
}