#include "Player.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <RandomEngine/API/Math/Functions.hpp>
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include <RandomEngine/API/Auxiliary/print_vectors.hpp>
#include <RandomEngine/API/System/Mouse.hpp>
#include <RandomEngine/API/System/Keyboard.hpp>
#include <RandomEngine/API/Graphics/Shape.hpp>
#include "Game/Settings.hpp"

namespace game
{
	void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (Settings::show_player_path)
		{
			target.draw(path_vertices.data(), path_vertices.size(), sf::PrimitiveType::LinesStrip, states);
		}

		
		sprite.setPosition(getPosition());
		sprite.setScale(getScale());
		sprite.setRotation(getRotation());
		target.draw(sprite, states);

		if (Settings::show_hitboxes)
		{
			Shape::createRectangle(Rect{
				getPosition() - getScale() * 0.5f,
				getPosition() + getScale() * 0.5f}, hitbox_vertices);
			target.draw(hitbox_vertices, 5, sf::LineStrip, states);
		}
	}
	Player::Player()
		: game_mode(GameMode::cube)
	{
		for (auto& vert : hitbox_vertices)
			vert.color = { 255, 0, 0 };

		reset(CheckPoint({ 0.f, 0.f }, { 10.4f, 0.f }, GameMode::cube));
	}

	void Player::reset(const CheckPoint& checkpoint)
	{
		isDead = false;
		prev_position = checkpoint.position;
		setPosition(prev_position);
		direction = checkpoint.direction;
		game_mode = checkpoint.game_mode;

		path_vertices.clear();
		path_vertices.push_back(sf::Vertex(checkpoint.position, sf::Color::Green));
	}

	bool Player::isOnGround() const
	{
		return onGround;
	}
	void Player::jump(float strength)
	{
		direction.y = strength * game_mode.jumpStrength * -Math::sign(game_mode.gravity);
	}
	void Player::die()
	{
		isDead = true;
		//setColor({ 1.f, 0.f, 0.f });
	}
	void Player::handleEvents(const sf::Event& e)
	{
		if (e.type == sf::Event::MouseButtonPressed and
			e.mouseButton.button == sf::Mouse::Left)
			actionIsCommited = false;
	}
	void Player::update(float delta)
	{
		if (isDead)
			return;

		prev_position = getPosition();
		direction = game_mode.updateDirCallback(*this, direction, delta);
		if (Mouse::isPressed(sf::Mouse::Left))
		{
			game_mode.onClickOnGround(*this);
			game_mode.onClick(*this);
			game_mode.onHoldOnGround(*this);
			game_mode.onHold(*this, delta);
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
	void Player::collisionProcess(const StaticBody& body)
	{
		switch (body.collisionMode)
		{
		case StaticBody::Repulsion:
		{
			auto result = body.getRepulsionVector(*this);
			if (result.touches)
			{
				if (result.offset.x != 0)
				{
					die();
				}
				direction.y = result.direction.y;
				move(vec2(0.f, result.offset.y));
				/* the object is at the bottom and gravity is directed downgard, or vice versa */
				if (Math::sign(result.offset.y) != Math::sign(game_mode.gravity))
					onGround = true;
			}
			break;
		}
		case StaticBody::Touch:
			if (body.action and body.touches(*this))
				body.action(*this);
			break;
		case StaticBody::OnClick:
			if (body.action and
				not actionIsCommited and
				Mouse::isPressed(sf::Mouse::Left) and 
				body.touches(*this))
			{
				body.action(*this);
				actionIsCommited = true;
			}
			break;
		}
		
	}
	bool Player::testCollisions(const StaticBody& body) const
	{
		if (body.collisionMode == StaticBody::Repulsion)
		{
			auto result = body.getRepulsionVector(*this);
			if (result.touches)
			{
				if (std::abs(result.offset.y) >= 0.001f)
				{
					PRINT(result.offset);
					return true;
				}
			}
		}
		
		return false;
	}
	void Player::collisionEnd()
	{
		if (Settings::show_player_path)
		{
			path_vertices.push_back(sf::Vertex(getPosition(), sf::Color::Green));
		}
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