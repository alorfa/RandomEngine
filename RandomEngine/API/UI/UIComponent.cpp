#include "UIComponent.hpp"
#include "RandomEngine/API/UI.hpp"

namespace random_engine
{
	void UIComponent::registerComponent(UIComponent& comp)
	{
		comp.owner = this;
		comp.camera = camera;
		comps.push_back(&comp);
	}
	void UIComponent::setCompAlignment(sf::Transformable& comp, int alignment, const vec2& position)
	{
		vec2 pos;
		if (alignment & UI::Left)
			pos.x = -camera->getNativeSize().x * 0.5f;
		if (alignment & UI::Right)
			pos.x = camera->getNativeSize().x * 0.5f;
		if (alignment & UI::Top)
			pos.y = camera->getNativeSize().y * 0.5f;
		if (alignment & UI::Bottom)
			pos.y = -camera->getNativeSize().y * 0.5f;

		comp.setPosition(pos + position);
	}
}