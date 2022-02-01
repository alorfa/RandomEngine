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
		UI();
		UI(const Camera& camera);

		void registerComponent(UIComponent& component);

		enum CompAlignment
		{
			None = 0,
			Left = 1 << 0, 
			Right = 1 << 1,
			Top = 1 << 2,
			Bottom = 1 << 3,
		};
		void setCompAlignment(sf::Transformable& comp, int alignment, const vec2& position);

		virtual void updateComponentsAlignment() = 0;
	};
}