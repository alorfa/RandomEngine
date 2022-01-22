#pragma once

#include "Scene.hpp"
#include "RandomEngine/API/Graphics/Camera.hpp"

namespace random_engine
{
	class UI : public Scene
	{
	protected:
		mutable Camera camera;
	public:

	};
}