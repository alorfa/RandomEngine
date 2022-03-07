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
		if (not view or view->type() != mode.type)
		{
			view = PlayerView::createView(mode.type, main_color, side_color, icons, *this);
		}
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
	void Player::updateView(float delta)
	{
		view->update(delta);
	}
}