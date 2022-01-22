#include "Mouse.hpp"
#include <SFML/Window/Mouse.hpp>
#include "RandomEngine/API/GlobalData.hpp"

namespace random_engine
{
	vec2 Mouse::getPosition(const Camera& camera)
	{
		sf::RenderWindow& window = GlobalData::getInstance().window;

		const sf::View& prev_view = window.getView();
		window.setView(camera.getSFMLView());
		vec2 result = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		window.setView(prev_view);
		return result;
	}
	vec2 Mouse::getPosition()
	{
		return getPosition(GlobalData::getInstance().camera);
	}
	bool Mouse::isPressed(Button button)
	{
		auto& window = GlobalData::getInstance().window;
		return window.hasFocus() &&
			sf::Mouse::isButtonPressed(button);
	}
}