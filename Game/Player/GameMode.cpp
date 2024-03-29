#include "GameMode.hpp"
#include "Game/Player.hpp"
#include <RandomEngine/API/Math/Functions.hpp>
#include "PlayerView/CubeView.hpp"

namespace
{
	vec2 default_dir_cb(const game::Player& p, vec2 dir, float delta) {
		dir.y += p.game_mode.gravity * delta;
		return dir;
	};
}

namespace game
{
	bool GameMode::onClick(Player& p) const
	{
		if (not p.actionIsCommited and onClickCallback)
		{
			onClickCallback(p, 0.f);
			p.actionIsCommited = true;
			return true;
		}
		return false;
	}
	bool GameMode::onClickOnGround(Player& p) const
	{
		if (not p.actionIsCommited and onClickOnGroundCallback and p.isOnGround())
		{
			onClickOnGroundCallback(p, 0.f);
			p.actionIsCommited = true;
			return true;
		}
		return false;
	}
	bool GameMode::onHold(Player& p, float delta) const
	{
		if (onHoldCallback)
		{
			onHoldCallback(p, delta);
			p.actionIsCommited = true;
			return true;
		}
		return false;
	}
	bool GameMode::onHoldOnGround(Player& p) const
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
		float jumpStrength,
		bool head_collision)

		: onClickCallback(onClick), 
		onClickOnGroundCallback(onClickOnGround),
		onHoldCallback(onHold),
		onHoldOnGroundCallback(onHoldOnGround),
		updateDirCallback(updateDir),
		gravity(gravity),
		jumpStrength(jumpStrength),
		head_collision(head_collision)
	{}

	GameModeInfo::GameModeInfo(PlayerView::Type type, 
		Callback onClick,
		Callback onClickOnGround,
		Callback onHold,
		Callback onHoldOnGround,
		UpdateDirectionCallback updateDir,
		float gravity,
		float jumpStrength,
		bool head_collision)

		: type(type),
		GameMode(onClick, onClickOnGround, onHold, onHoldOnGround, 
			updateDir, gravity, jumpStrength, head_collision)
	{}

	const GameModeInfo GameModeInfo::cube(PlayerView::Cube, nullptr, nullptr, nullptr, [](Player& p, float _) {
		p.jump(1.f);
	}, default_dir_cb, -70.f, 17.f
	);
	const GameModeInfo GameModeInfo::ship(PlayerView::Ship, nullptr, nullptr, [](Player& p, float delta) {
		p.direction.y += 90.f * delta  * -(float)Math::sign(p.game_mode.gravity);
	}, nullptr, default_dir_cb, -40.f, 17.f, true
	);
	const GameModeInfo GameModeInfo::ball(PlayerView::Ball, nullptr, [](Player& p, float delta) {
		p.jump(0.1f);
		p.game_mode.gravity *= -1.f;
		}, nullptr, nullptr, default_dir_cb, -45.f, 12.f, true
	);
}