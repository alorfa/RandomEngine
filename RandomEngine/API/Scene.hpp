#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

namespace random_engine
{
	class Scene : public sf::Drawable
	{
	protected:
		std::vector<Scene*> scenes;
	public:
		virtual void handleEvents(const sf::Event& e) = 0;
		virtual void update(float delta) = 0;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void registerScene(Scene& scene);

		Scene* owner = nullptr;

		template <typename T>
		bool is() const
		{
			return (bool)dynamic_cast<const T*>(this);
		}
		template <typename T>
		T& as()
		{
			return dynamic_cast<T&>(*this);
		}
	};
}