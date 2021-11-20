#include "Mouse.hpp"
#include <SFML/Window/Mouse.hpp>

namespace random_engine
{
	Vec2 Mouse::getPosition(const Camera& camera)
	{
		if (not window)
			return Vec2();

		Vec2u uwnd_size = window->getSize();
		Vec2 fwnd_size = uwnd_size.as<float>();

		Vec2i i_mouse = sf::Mouse::getPosition(*window);
		Vec2 rel_window_pos = i_mouse;
		rel_window_pos -= fwnd_size.as<float>() * 0.5f;
		rel_window_pos.x /= fwnd_size.x;
		rel_window_pos.y /= -fwnd_size.y;

		return rel_window_pos * camera.getSize() + camera.getPosition();
	}
	Vec2 Mouse::getPosition()
	{
		if (not camera)
			return Vec2();
		return getPosition(*camera);
	}
	void Mouse::setDefaultCamera(const Camera& camera)
	{
		Mouse::camera = &camera;
	}
	bool Mouse::isPressed(Button button)
	{
		return window &&
			window->hasFocus() &&
			sf::Mouse::isButtonPressed(button);
	}
	const sf::Window* Mouse::window = nullptr;
	const Camera* Mouse::camera = nullptr;
}