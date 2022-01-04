#pragma once

#include <RandomEngine/API/Math/vec2.hpp>

using namespace random_engine;

namespace game
{
	class Player;

	struct GameMode
	{
		using Callback = void (*)(Player&, float delta);
		using UpdateDirectionCallback = vec2(*)(const Player&, vec2 dir, float delta);

		Callback onClickCallback = nullptr;
		Callback onClickOnGroundCallback = nullptr;
		Callback onHoldCallback = nullptr;
		Callback onHoldOnGroundCallback = nullptr;
		UpdateDirectionCallback updateDirCallback = nullptr;

		bool onClick(Player& p);
		bool onClickOnGround(Player& p);
		bool onHold(Player& p, float delta);
		bool onHoldOnGround(Player& p);

		float gravity;
		float jumpStrength;

		static const GameMode cube;
		static const GameMode ship;

		GameMode(Callback onClick, Callback onClickOnGround, Callback onHold, Callback onHoldOnGround,
			UpdateDirectionCallback updateDir,
			float gravity, float jumpStrength);
	};
}