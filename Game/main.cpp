#include <iostream>
#include <RandomEngine/API/Application.hpp>

#include <RandomEngine/API/Math.hpp>
#include <RandomEngine/API/Graphics/Circle.hpp>
#include <RandomEngine/API/System/Mouse.hpp>
#include <RandomEngine/API/Resource/TextureLoader.hpp>
#include <RandomEngine/API/Graphics/Sprite.hpp>
#include <RandomEngine/API/Math/Smoother.hpp>

#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include <RandomEngine/API/Auxiliary/print_vectors.hpp>

using namespace random_engine;

namespace
{
}

class MyGame : public Application
{
	struct EventData
	{
		vec2 player_direction;
		vec2 player_pos;
	};
	EventData events;

	Circle circle;
	Sprite sprite;

	Texture t;

protected:
	void appInit() override
	{
		camera.setScale({ 1, 1 });
		camera.setPosition({ 0, 0 });

		circle.create(50);
		circle.setScale({ 0.5f, 0.5f });
	}
	void loadResources() override
	{
		sprite.setTexture(textureLoader.load(res / "img/image.jpg"));
		sprite.align(Sprite::MaxOne);
	}
	void startGame() override
	{

	}
	void handleEvent(const sf::Event& e) override
	{
		events.player_direction = vec2();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			events.player_direction.x -= 1.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			events.player_direction.x += 1.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			events.player_direction.y -= 1.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			events.player_direction.y += 1.f;

		events.player_direction.normalize();
	}
	void update(float base_delta, float delta) override
	{
		events.player_pos += events.player_direction * delta * 2.f;

		camera.setPosition(Smoother::linear(camera.getPosition(), events.player_pos, 20.f, delta));

		vec2 mouse_position = Mouse::getPosition();

		vec2 next_pos = Smoother::linear(circle.getPosition(), mouse_position, 1.f, delta);
		circle.setPosition(next_pos);

		PRINTR(1.f / delta);
	}
	void draw(sf::RenderTarget& window) const override
	{
		window.draw(circle);
		window.draw(sprite);
	}
	void appEnd() override
	{

	}
public:
};

int main()
{
	MyGame game;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	game.res = "res";
	game.run({800, 800}, "title", sf::Style::Default, settings);

	return 0;
}