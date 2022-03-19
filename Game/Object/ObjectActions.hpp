#pragma once

namespace game
{
	class Player;

	class ObjectActions
	{
	public:
		static void die(Player& p);
		static void normalJump(Player& p);
		static void littleJump(Player& p);
		static void toShip(Player& p);
		static void toCube(Player& p);
		static void toBall(Player& p);
	};
}