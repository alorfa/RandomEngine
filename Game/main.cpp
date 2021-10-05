#include <iostream>
#include <RandomEngine/API/Application.hpp>

#include <RandomEngine/API/Math.hpp>
#include <RandomEngine/API/Graphics/Circle.hpp>
#include <RandomEngine/API/System/Mouse.hpp>
#include <RandomEngine/API/Resource/TextureLoader.hpp>
#include <RandomEngine/API/Graphics/Sprite.hpp>
#include <RandomEngine/API/Math/MovementSmoother.hpp>

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


	void loadResources()
	{
		sprite.texture = &textureLoader.load(res / "img/image.jpg");
		vec2 size = sprite.texture->getSize();
		float max = std::max(size.x, size.y);
		sprite.setScale(size.x / max, size.y / max);
	}
protected:
	void appInit() override
	{
		camera.setScale({ 1, 1 });
		camera.setPosition({0, 0});

		circle.create(50);
		circle.setScale({ 0.5f, 0.5f });
		sprite.setArea({ 0.f, 0.f }, { 1.f, 1.f });
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
	void everyFrame(float base_delta, float delta) override
	{
		events.player_pos += events.player_direction * delta * 2.f;

		camera.setPosition(events.player_pos);

		vec2 mouse_position = Mouse::getPosition();

		vec2 next_pos = Interpolation::linear<vec2>(circle.getPosition(), mouse_position, 120.f * delta);
		circle.setPosition(next_pos);
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
	//MyGame() {}
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