#include "Tabs.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "RandomEngine/API/Auxiliary/DEBUG.hpp"

namespace random_engine
{
	Tabs::Tabs()
	{
	}
	void Tabs::setTab(std::unique_ptr<Tab> new_tab)
	{
		registerComponent(new_tab->tab);
		for (auto& comp : new_tab->comps)
			registerComponent(*comp);

		new_tab->tab.onReleased = [](Button& self) {
			self.owner->as<Tabs>().setActiveTab(&self);
		};

		for (auto& tab : tabs)
		{
			if (tab->name == new_tab->name) {

				std::swap(tab, new_tab);
				return;
			}
		}
		tabs.push_back(std::move(new_tab));
	}
	void Tabs::removeTab(const std::string& name)
	{
		for (auto it = tabs.begin(); it != tabs.end(); ++it)
		{
			if (it->get()->name == name) {
				if (active_tab == it->get())
					active_tab = nullptr;

				tabs.erase(it);
				return;
			}
		}
	}
	void Tabs::setActiveTab(const std::string& name)
	{
		for (auto& tab : tabs)
		{
			if (tab->name == name)
			{
				active_tab = tab.get();
				return;
			}
		}
	}
	void Tabs::setActiveTab(const Button* button)
	{
		for (auto& tab : tabs)
		{
			if (&tab->tab == button)
			{
				active_tab = tab.get();
				return;
			}
		}
	}
	void Tabs::updateComponentsAlignment()
	{

	}
	void Tabs::handleEvents(const sf::Event& e)
	{
		// update active tab
		for (auto& tab : tabs)
			tab->tab.handleEvents(e);

		if (active_tab)
			for (auto& comp : active_tab->comps)
				comp->handleEvents(e);
	}
	void Tabs::update(float delta)
	{
		for (auto& tab : tabs)
			tab->tab.update(delta);

		if (active_tab)
			for (auto& comp : active_tab->comps)
				comp->update(delta);
	}
	void Tabs::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const auto& tab : tabs)
			target.draw(tab->tab, states);

		if (active_tab)
			for (const auto& comp : active_tab->comps)
				target.draw(*comp, states);
	}
}