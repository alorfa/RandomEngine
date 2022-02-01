#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include "RandomEngine/API/Scene.hpp"
#include "RandomEngine/API/Math/vec2.hpp"

namespace random_engine
{
	class Camera;

	class UIComponent : public Scene
	{
	protected:
		std::vector<UIComponent*> comps;
	public:
		const Camera* camera = nullptr;

		void registerComponent(UIComponent& comp);

		void setCompAlignment(sf::Transformable& comp, int alignment, const vec2& position);
		virtual void updateComponentsAlignment() = 0;
	};
}