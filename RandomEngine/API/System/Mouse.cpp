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
	vec2 Mouse::getOffset(const vec2& camera_size, const ivec2& pixel_offset)
	{
		const sf::Window& window = GlobalData::getInstance().window;

		uvec2 uwnd_size = window.getSize();
		vec2 fwnd_size = uwnd_size.as<float>();

		vec2 rel_window_pos = pixel_offset;
		rel_window_pos.x /= fwnd_size.x;
		rel_window_pos.y /= -fwnd_size.y;

		return rel_window_pos * camera_size;
	}
	bool Mouse::isPressed(Button button)
	{
		auto& window = GlobalData::getInstance().window;
		return window.hasFocus() &&
			sf::Mouse::isButtonPressed(button);
	}
}