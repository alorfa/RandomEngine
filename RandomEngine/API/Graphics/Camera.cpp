#include "Camera.hpp"

namespace random_engine
{
	const Camera& Camera::getDefault()
	{
		if (not default_camera)
		{
			Camera* c = new Camera;
			c->setSize(1, 1);
			default_camera = c;
		}
		return *default_camera;
	}
	Camera* Camera::default_camera = nullptr;
}