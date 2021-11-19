#include "Player.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <RandomEngine/API/Math/Functions.hpp>
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include <RandomEngine/API/System/Mouse.hpp>

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
		direction.x = 0.6f;

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
		for (const auto& vector : touchVectors)
			/* the object is at the bottom and gravity is directed downgard, or vice versa */
			if (Math::sign(vector.y) == Math::sign(gravity))
				return true;
		return false;
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
	void Player::collisionProcess(const std::vector<const StaticBody*>& bodies)
	{
		touchVectors.clear();

		for (const auto* body : bodies)
		{
			switch (body->collisionMode)
			{
			case StaticBody::Repulsion:
			{
				auto result = body->getRepulsionVector(*this);
				if (result.touches)
				{
					direction = result.direction;
					move(result.offset);
					touchVectors.push_back(-result.offset);
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
	void Player::setColor(const color3f& color)
	{
		auto* vertices = sprite.changeVertices();
		for (int i = 0; i < 4; i++)
			vertices[i].color = color.toSfColor();
	}
}