#include "UI.hpp"

#include "UI/UIComponent.hpp"

namespace random_engine
{
	void UI::registerComponent(UIComponent& component)
	{
		component.camera = &camera;
		component.owner = this;
		components.push_back(&component);
	}
}