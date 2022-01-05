#include "Camera.hpp"

namespace random_engine
{
	Camera::Camera(const sf::Window& wnd)
	{
		native_size_handler = defaultSizeHandler;
		camera.setSize(1.f, 1.f);
	}
	Camera::Camera()
	{
		native_size_handler = defaultSizeHandler;
		setSize(1.f, 1.f);
	}
	void Camera::updateNativeSize()
	{
		vec2 new_size = native_size_handler(size, *window);
		new_size.y *= -1;
		camera.setSize(new_size);
	}
	const Camera& Camera::getDefault()
	{
		if (not default_camera)
		{
			Camera* c = new Camera;
			c->setSize(1.f, 1.f);
			default_camera = c;
		}
		return *default_camera;
	}
	vec2 Camera::defaultSizeHandler(const vec2& size, const sf::Window& window)
	{
		const vec2 wsize = window.getSize();
		const float aspect_ratio = wsize.x / wsize.y;
		return vec2(size.x * aspect_ratio, size.y);
	}
	Camera* Camera::default_camera = nullptr;
	const sf::Window* Camera::window = nullptr;
}