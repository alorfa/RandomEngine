#include "Player.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <RandomEngine/API/Math/Functions.hpp>
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include <RandomEngine/API/Auxiliary/print_vectors.hpp>
#include <RandomEngine/API/System/Mouse.hpp>
#include <RandomEngine/API/System/Keyboard.hpp>
#include <RandomEngine/API/Graphics/Shape.hpp>
#include <RandomEngine/API/GlobalData.hpp>
#include <RandomEngine/API/Resource/SoundLoader.hpp>
#include "Game/Settings.hpp"

namespace game
{
	void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		view->draw(target, states);

		if (Settings::show_hitboxes)
		{
			Shape::createRectangle(Rect{
				getPosition() - getScale() * 0.5f,
				getPosition() + getScale() * 0.5f}, hitbox_vertices);
			target.draw(hitbox_vertices, 5, sf::LineStrip, states);

			Shape::createRectangle(getDeathArea(), death_area_vertices);
			target.draw(death_area_vertices, 5, sf::LinesStrip, states);
		}
	}
	void Player::drawPath(sf::RenderTarget& target, const sf::RenderStates& states) const
	{
		target.draw(path_vertices.data(), path_vertices.size(), sf::PrimitiveType::LinesStrip, states);
	}
	Player::Player()
		: game_mode(GameModeInfo::cube)
	{
		main_color = sf::Color::Green;
		side_color = sf::Color::Cyan;

		for (size_t i = 0; i < 5; i++)
		{
			hitbox_vertices[i].color = sf::Color::Green;
			death_area_vertices[i].color = sf::Color::Red;
		}

		reset(CheckPoint({ 0.f, 0.f }, { 10.4f, 0.f }, GameModeInfo::cube));
	}

	void Player::reset(const CheckPoint& checkpoint)
	{
		isDead = false;
		prev_position = checkpoint.position;
		setPosition(prev_position);
		direction = checkpoint.direction;
		setGameMode(checkpoint.game_mode);

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
		if (isDead)
			return;

		isDead = true;
		sound.setBuffer(soundLoader.load(res / "sounds/explode_11.ogg"));
		sound.play();
	}
	void Player::setGameMode(const GameModeInfo& mode)
	{
		game_mode = mode;
		view = PlayerView::createView(mode.type, main_color, side_color, icons, *this);
	}
	void Player::handleEvents(const sf::Event& e)
	{
		if (e.type == sf::Event::MouseButtonPressed)
		{
			actionIsCommited = false;
			is_pressed = true;
		}
		if (e.type == sf::Event::MouseButtonReleased)
		{
			is_pressed = false;
		}
	}
	void Player::update(float delta)
	{
		if (isDead)
			return;

		prev_position = getPosition();
		direction = game_mode.updateDirCallback(*this, direction, delta);
		if (is_pressed)
		{
			game_mode.onClickOnGround(*this);
			game_mode.onClick(*this);
			game_mode.onHoldOnGround(*this);
			game_mode.onHold(*this, delta);
		}
		move(direction * delta);
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
			auto result = body.getRepulsionVector(getPhysicalRect());
			if (result.touches)
			{
				if (Math::sign(result.offset.y) != Math::sign(game_mode.gravity))
				{
					direction.y = result.direction.y;
					move(vec2(0.f, result.offset.y));
					/* the object is at the bottom and gravity is directed downgard, or vice versa */
					if (Math::sign(result.offset.y) != Math::sign(game_mode.gravity))
						onGround = true;
				}
				if (game_mode.head_collision and
					Math::sign(result.offset.y) == Math::sign(game_mode.gravity))
				{
					direction.y = result.direction.y;
					move(vec2(0.f, result.offset.y));
				}
				
			}
			break;
		}
		case StaticBody::Touch:
			if (body.action and body.touches(getPhysicalRect()))
				body.action(*this);
			break;
		case StaticBody::OnClick:
			if (body.action and
				not actionIsCommited and
				Mouse::isPressed(sf::Mouse::Left) and 
				body.touches(getPhysicalRect()))
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
			auto result = body.getRepulsionVector(getDeathArea());
			return result.touches;
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
	const PhysicalRect& Player::getPhysicalRect() const
	{
		physical_rect.direction = direction;
		physical_rect.min = getPosition() - getScale() * 0.5f;
		physical_rect.max = physical_rect.min + getScale();
		physical_rect.center = getPosition();
		physical_rect.movement = getPosition() - getPrevPos();
		return physical_rect;
	}
	const PhysicalRect& Player::getDeathArea() const
	{
		death_area.direction = direction;
		death_area.min = getPosition() - getScale() * 0.5f * 0.33f;
		death_area.max = death_area.min + getScale() * 0.33f;
		death_area.center = getPosition();
		death_area.movement = getPosition() - getPrevPos();
		return death_area;
	}
}