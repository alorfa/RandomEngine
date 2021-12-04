#include "Player.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <RandomEngine/API/Math/Functions.hpp>
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include <RandomEngine/API/System/Mouse.hpp>
#include <RandomEngine/API/Auxiliary/print_vectors.hpp>

namespace game
{
	void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		sprite.setPosition(getPosition());
		sprite.setScale(getScale());
		sprite.setRotation(getRotation());
		target.draw(sprite);
	}
	Player::Player()
	{
		direction.x = 1.6f;

		setUpdateDirectionCallback([](const Player& p, vec2 dir, float delta) -> vec2 {
			dir.y += p.gravity * delta;
			return dir;
		});
	}

	void Player::setOnClickCallback(Callback callback)
	{
		onClickCallback = callback;
	}
	void Player::setOnClickOnGroundCallback(Callback callback)
	{
		onClickOnGroundCallback = callback;
	}
	void Player::setOnHoldCallback(Callback callback)
	{
		onHoldCallback = callback;
	}
	void Player::setOnHoldOnGroundCallback(Callback callback)
	{
		onHoldOnGroundCallback = callback;
	}

	void Player::setUpdateDirectionCallback(UpdateDirectionCallback callback)
	{
		updateDirCallback = callback;
	}

	bool Player::isOnGround() const
	{
		return onGround;
	}
	bool Player::onClick()
	{
		if (not actionIsCommited and onClickCallback)
		{
			onClickCallback(*this, 0.f);
			actionIsCommited = true;
			return true;
		}
		return false;
	}
	bool Player::onClickOnGround()
	{
		if (not actionIsCommited and onClickOnGroundCallback and isOnGround())
		{
			onClickOnGroundCallback(*this, 0.f);
			actionIsCommited = true;
			return true;
		}
		return false;
	}
	bool Player::onHoldOnGround()
	{
		if (onHoldOnGroundCallback and isOnGround())
		{
			onHoldOnGroundCallback(*this, 0.f);
			actionIsCommited = true;
			return true;
		}
		return false;
	}
	bool Player::onHold(float delta)
	{
		if (onHoldCallback)
		{
			onHoldCallback(*this, delta);
			actionIsCommited = true;
			return true;
		}
		return false;
	}
	void Player::jump(float strength)
	{
		direction.y = strength * -Math::sign(gravity);
	}
	void Player::die()
	{
		setColor({ 1.f, 0.f, 0.f });
	}
	void Player::handleEvents(const sf::Event& e)
	{
		if (e.type == sf::Event::MouseButtonPressed and
			e.mouseButton.button == sf::Mouse::Left)
			actionIsCommited = false;
	}
	void Player::update(float delta)
	{
		prev_position = getPosition();
		direction = updateDirCallback(*this, direction, delta);
		if (Mouse::isPressed(sf::Mouse::Left))
		{
			onClickOnGround();
			onClick();
			onHoldOnGround();
			onHold(delta);
		}
		move(direction * delta);
		setColor({ 1.f, 1.f, 1.f });
	}
	void Player::setTexture(const Texture& t)
	{
		sprite.setTexture(t);
	}
	void Player::collisionBegin()
	{
		onGround = false;
	}
	void Player::collisionProcess(const std::vector<const StaticBody*>& bodies)
	{
		for (const auto* body : bodies)
		{
			switch (body->collisionMode)
			{
			case StaticBody::Repulsion:
			{
				auto result = body->getRepulsionVector(*this);
				if (result.touches)
				{
					if (result.offset.x != 0)
					{
						die();
					}
					direction.y = result.direction.y;
					move(vec2(0.f, result.offset.y));
					/* the object is at the bottom and gravity is directed downgard, or vice versa */
					if (Math::sign(result.offset.y) != Math::sign(gravity))
						onGround = true;
				}
				break;
			}
			case StaticBody::Touch:
				if (body->action and body->touches(*this))
					body->action(*this);
				break;
			}
		}
	}
	bool Player::testCollisions(const std::vector<const StaticBody*>& bodies) const
	{
		for (const auto* body : bodies)
		{
			if (body->collisionMode == StaticBody::Repulsion)
			{
				auto result = body->getRepulsionVector(*this);
				if (result.touches)
				{
					return fabs(result.offset.y) > 0.1f;
				}
			}
		}
		return false;
	}
	void Player::setColor(const color3f& color)
	{
		auto* vertices = sprite.changeVertices();
		for (int i = 0; i < 4; i++)
			vertices[i].color = color.toSfColor();
	}
	const PhysicalRect& Player::getPhysicalRect() const
	{
		physical_rect.direction = direction;
		physical_rect.min = getPosition() - getScale() * 0.5f;
		physical_rect.max = physical_rect.min + getScale();
		physical_rect.center = getPosition();
		physical_rect.movement = getPosition() - getPrevPos();
		return physical_rect;
	}
}