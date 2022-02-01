#include "UI.hpp"

#include "UI/UIComponent.hpp"

namespace random_engine
{
	UI::UI()
	{
	}
	UI::UI(const Camera& camera)
		: camera(camera)
	{
	}
	void UI::registerComponent(UIComponent& component)
	{
		component.camera = &camera;
		component.owner = this;
		components.push_back(&component);
	}
	void UI::setCompAlignment(sf::Transformable& comp, int alignment, const vec2& position)
	{
		vec2 pos;
		if (alignment & Left)
			pos.x = -camera.getNativeSize().x * 0.5f;
		if (alignment & Right)
			pos.x = camera.getNativeSize().x * 0.5f;
		if (alignment & Top)
			pos.y = camera.getNativeSize().y * 0.5f;
		if (alignment & Bottom)
			pos.y = -camera.getNativeSize().y * 0.5f;

		comp.setPosition(pos + position);
	}
}