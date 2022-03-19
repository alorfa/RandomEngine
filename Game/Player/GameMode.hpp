#pragma once

#include <RandomEngine/API/Math/vec2.hpp>
#include "Game/Player/PlayerView.hpp"

using namespace random_engine;

namespace game
{
	class Player;

	struct GameMode
	{
	public:
		using Callback = void (*)(Player&, float delta);
		using UpdateDirectionCallback = vec2(*)(const Player&, vec2 dir, float delta);

		Callback onClickCallback = nullptr;
		Callback onClickOnGroundCallback = nullptr;
		Callback onHoldCallback = nullptr;
		Callback onHoldOnGroundCallback = nullptr;
		UpdateDirectionCallback updateDirCallback = nullptr;

		bool onClick(Player& p) const;
		bool onClickOnGround(Player& p) const;
		bool onHold(Player& p, float delta) const;
		bool onHoldOnGround(Player& p) const;

		float gravity;
		float jumpStrength;

		bool head_collision;

		GameMode(Callback onClick, Callback onClickOnGround, Callback onHold, Callback onHoldOnGround,
			UpdateDirectionCallback updateDir,
			float gravity, float jumpStrength, bool head_collision = false);
	};

	struct GameModeInfo : GameMode
	{
		PlayerView::Type type;

		static const GameModeInfo cube;
		static const GameModeInfo ship;
		static const GameModeInfo ball;

		GameModeInfo(PlayerView::Type type,
			Callback onClick, Callback onClickOnGround, Callback onHold, Callback onHoldOnGround,
			UpdateDirectionCallback updateDir,
			float gravity, float jumpStrength, bool head_collision = false);
	};
}