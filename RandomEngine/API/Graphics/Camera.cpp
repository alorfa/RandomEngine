#include "Camera.hpp"
#include "RandomEngine/API/Application.hpp"

namespace random_engine
{
	Camera::Camera(const sf::Window& wnd)
	{
		window = &wnd;
		native_size_handler = defaultSizeHandler;
		setSize(1.f, 1.f);
		setPosition(0.f, 0.f);
	}
	Camera::Camera()
	{
		native_size_handler = defaultSizeHandler;
		setSize(1.f, 1.f);
		setPosition(0.f, 0.f);
	}
	Camera::Camera(const vec2& pos, float rot, const vec2& size)
	{
		native_size_handler = defaultSizeHandler;
		setPosition(pos);
		setRotation(rot);
		setSize(size);
	}
	void Camera::updateNativeSize()
	{
		vec2 new_size = native_size_handler(size, *window);
		new_size.y *= -1;
		camera.setSize(new_size);
	}
	vec2 Camera::defaultSizeHandler(const vec2& size, const sf::Window& wnd)
	{
		const vec2 wsize = wnd.getSize();
		const float aspect_ratio = wsize.x / wsize.y;
		return vec2(size.x * aspect_ratio, size.y);
	}
	const sf::Window* Camera::window = nullptr;
}