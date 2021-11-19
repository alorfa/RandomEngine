#include "Mouse.hpp"
#include <SFML/Window/Mouse.hpp>

namespace random_engine
{
	vec2 Mouse::getPosition(const Camera& camera)
	{
		if (not window)
			return vec2();

		uvec2 uwnd_size = window->getSize();
		vec2 fwnd_size = uwnd_size.as<float>();

		ivec2 i_mouse = sf::Mouse::getPosition(*window);
		vec2 rel_window_pos = i_mouse;
		rel_window_pos -= fwnd_size.as<float>() * 0.5f;
		rel_window_pos.x /= fwnd_size.x;
		rel_window_pos.y /= -fwnd_size.y;

		return rel_window_pos * camera.getSize() + camera.getPosition();
	}
	vec2 Mouse::getPosition()
	{
		if (not camera)
			return vec2();
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