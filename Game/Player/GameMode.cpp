#include "GameMode.hpp"
#include "Game/Player.hpp"
#include <RandomEngine/API/Math/Functions.hpp>

namespace
{
	vec2 default_dir_cb(const game::Player& p, vec2 dir, float delta) {
		dir.y += p.game_mode.gravity * delta;
		return dir;
	};
}

namespace game
{
	bool GameMode::onClick(Player& p)
	{
		if (not p.actionIsCommited and onClickCallback)
		{
			onClickCallback(p, 0.f);
			p.actionIsCommited = true;
			return true;
		}
		return false;
	}
	bool GameMode::onClickOnGround(Player& p)
	{
		if (not p.actionIsCommited and onClickOnGroundCallback and p.isOnGround())
		{
			onClickOnGroundCallback(p, 0.f);
			p.actionIsCommited = true;
			return true;
		}
		return false;
	}
	bool GameMode::onHold(Player& p, float delta)
	{
		if (onHoldCallback)
		{
			onHoldCallback(p, delta);
			p.actionIsCommited = true;
			return true;
		}
		return false;
	}
	bool GameMode::onHoldOnGround(Player& p)
	{
		if (onHoldOnGroundCallback and p.isOnGround())
		{
			onHoldOnGroundCallback(p, 0.f);
			p.actionIsCommited = true;
			return true;
		}
		return false;
	}
	GameMode::GameMode(Callback onClick,
		Callback onClickOnGround, 
		Callback onHold, 
		Callback onHoldOnGround, 
		UpdateDirectionCallback updateDir, 
		float gravity, 
		float jumpStrength)

		: onClickCallback(onClick), 
		onClickOnGroundCallback(onClickOnGround),
		onHoldCallback(onHold),
		onHoldOnGroundCallback(onHoldOnGround),
		updateDirCallback(updateDir),
		gravity(gravity),
		jumpStrength(jumpStrength)
	{}

	const GameMode GameMode::cube(nullptr, nullptr, nullptr, [](Player& p, float _) {
		p.jump(1.f);
	}, default_dir_cb, -70.f, 17.f
	);
	const GameMode GameMode::ship(nullptr, nullptr, [](Player& p, float delta) {
		p.direction.y += 90.f * delta  * -Math::sign(p.game_mode.gravity);
	}, nullptr, default_dir_cb, -40.f, 17.f
	);
}