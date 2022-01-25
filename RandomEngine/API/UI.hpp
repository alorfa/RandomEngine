#pragma once

#include "Scene.hpp"
#include "RandomEngine/API/Graphics/Camera.hpp"

namespace random_engine
{
	class UIComponent;

	class UI : public Scene
	{
	protected:
		mutable Camera camera;
		std::vector<UIComponent*> components;
	public:
		void registerComponent(UIComponent& component);
	};
}