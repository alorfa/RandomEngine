#pragma once

#include "Button.hpp"
#include <vector>
#include <map>
#include "RandomEngine/API/UI.hpp"

namespace random_engine
{
	class Tabs : public UIComponent
	{
	public:
		using ComponentsList = std::vector<std::unique_ptr<UIComponent>>;
		struct Tab
		{
			Button tab;
			ComponentsList comps;
			std::string name;
		};
	private:
		std::vector<std::unique_ptr<Tab>> tabs;
		Tab* active_tab = nullptr;
	public:
		Tabs();

		inline const auto& getTabs() const {
			return tabs;
		}
		void setTab(std::unique_ptr<Tab> tab);
		void removeTab(const std::string& name);

		inline Tab* getActiveTab() {
			return active_tab;
		}
		void setActiveTab(const std::string& name);
		void setActiveTab(const Button* button);

		void updateComponentsAlignment() override;
		void handleEvents(const sf::Event& e) override;
		void update(float delta) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}