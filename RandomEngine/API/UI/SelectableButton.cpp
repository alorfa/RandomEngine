#include "SelectableButton.hpp"

namespace random_engine
{
	void SelectableButton::select()
	{
		selected = true;
		sprite.setColor(select_color);
	}
	void SelectableButton::deselect()
	{
		selected = false;
		sprite.setColor(sf::Color::White);
	}
}