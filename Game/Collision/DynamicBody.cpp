#include "DynamicBody.hpp"
#include <RandomEngine/API/Math/Functions.hpp>
#include <RandomEngine/API/System/Mouse.hpp>
#include "Game/Collision/StaticBody.hpp"
#include "Game/Player.hpp"
#include "Game/Settings.hpp"

namespace game
{
	bool DynamicBody::isOnGround() const
	{
		return onGround;
	}
	void DynamicBody::collisionBegin()
	{
		onGround = false;
		contact_offsets.clear();
	}
	void DynamicBody::collisionProcess(const StaticBody& body)
	{
		auto& player = as<Player>();
		switch (body.collisionMode)
		{
		case StaticBody::Repulsion:
		{
			auto result = body.getRepulsionVector(getPhysicalRect());
			if (result.touches)
			{
				if (Math::sign(result.offset.y) != Math::sign(player.game_mode.gravity))
				{
					contact_offsets.push_back(result.offset);
					direction.y = result.direction.y;
					move(vec2(0.f, result.offset.y));
					/* the object is at the bottom and gravity is directed downgard, or vice versa */
					if (Math::sign(result.offset.y) != Math::sign(player.game_mode.gravity))
						onGround = true;
				}
				if (player.game_mode.head_collision and
					Math::sign(result.offset.y) == Math::sign(player.game_mode.gravity))
				{
					contact_offsets.push_back(result.direction);
					direction.y = result.direction.y;
					move(vec2(0.f, result.offset.y));
				}

			}
			break;
		}
		case StaticBody::Touch:
			if (body.action and body.touches(getPhysicalRect()))
				body.action(player);
			break;
		case StaticBody::OnClick:
			if (body.action and
				not player.actionIsCommited and
				Mouse::isPressed(sf::Mouse::Left) and
				body.touches(getPhysicalRect()))
			{
				body.action(player);
				player.actionIsCommited = true;
			}
			break;
		}

	}
	bool DynamicBody::testCollisions(const StaticBody& body) const
	{
		if (body.collisionMode == StaticBody::Repulsion)
		{
			auto result = body.getRepulsionVector(getDeathArea());
			return result.touches;
		}

		return false;
	}
	void DynamicBody::collisionEnd()
	{
		if (Settings::show_player_path)
		{
			as<Player>().path_vertices.push_back(sf::Vertex(getPosition(), sf::Color::Green));
		}
	}
	const PhysicalRect& DynamicBody::getPhysicalRect() const
	{
		physical_rect.direction = direction;
		physical_rect.min = getPosition() - getScale() * 0.5f;
		physical_rect.max = physical_rect.min + getScale();
		physical_rect.center = getPosition();
		physical_rect.movement = getPosition() - getPrevPos();
		return physical_rect;
	}
	const PhysicalRect& DynamicBody::getDeathArea() const
	{
		death_area.direction = direction;
		death_area.min = getPosition() - getScale() * 0.5f * 0.33f;
		death_area.max = death_area.min + getScale() * 0.33f;
		death_area.center = getPosition();
		death_area.movement = getPosition() - getPrevPos();
		return death_area;
	}
	const std::vector<vec2>& DynamicBody::getContactOffsets() const
	{
		return contact_offsets;
	}
}