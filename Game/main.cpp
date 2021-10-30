#include <iostream>
#include <RandomEngine/API/Application.hpp>

#include <RandomEngine/API/Math.hpp>
#include <RandomEngine/API/Graphics/VertexObject.hpp>
#include <RandomEngine/API/Graphics/Sprite.hpp>
#include <RandomEngine/API/Graphics/Shape.hpp>
#include <RandomEngine/API/System/Mouse.hpp>
#include <RandomEngine/API/Resource/TextureLoader.hpp>
#include <RandomEngine/API/Math/Functions.hpp>

#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include <RandomEngine/API/Auxiliary/print_vectors.hpp>

#include <RandomEngine/API/Tests/ShapeTests.hpp>

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

	VertexObject circles[2];
	Sprite sprite;

	Texture t;

protected:
	void appInit() override
	{
		camera.setScale({ 1, 1 });
		camera.setPosition({ 0, 0 });

		circles[0].vertices = circles[1].vertices = Shape::createCircle(100);
		circles[0].drawVertCount = circles[1].drawVertCount = Shape::getVertexCount(50, sf::TriangleFan);
		circles[0].setScale({ 0.5f, 0.5f });
		circles[0].setPosition({-0.25f, 0.f});
		circles[1].setScale({ 1.f, 1.f });
		circles[1].setPosition({ 0.5f, 0.f });
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			circles[0].rotate(-10.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			circles[0].rotate(10.f);

		events.player_direction.normalize();
	}
	void update(float base_delta, float delta) override
	{
		events.player_pos += events.player_direction * delta * 2.f;

		camera.setPosition(Math::linearSmooth(camera.getPosition(), events.player_pos, 20.f, delta));

		vec2 mouse_position = Mouse::getPosition();

		vec2 next_pos = Math::linearSmooth(circles[0].getPosition(), mouse_position, 10.f, delta);
		circles[0].setPosition(next_pos);

		//PRINTR(1.f / delta);
	}
	void draw(sf::RenderTarget& window) const override
	{
		window.draw(circles[0]);
		window.draw(circles[1]);
	}
	void appEnd() override
	{

	}
public:
};

int main()
{
	//random_engine::shape_Tests();
	//return 0;

	MyGame game;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	game.res = "res";
	game.run({800, 800}, "title", sf::Style::Default, settings);

	return 0;
}