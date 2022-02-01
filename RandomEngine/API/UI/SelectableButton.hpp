#pragma once

#include <RandomEngine/API/UI/Button.hpp>

namespace random_engine
{
	class SelectableButton : public Button
	{
		bool selected = false;
	public:
		sf::Color select_color;

		void select();
		void deselect();

		inline bool isSelected() const {
			return selected;
		}
	};
}