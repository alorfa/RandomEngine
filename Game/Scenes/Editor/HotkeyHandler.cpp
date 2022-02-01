#include "HotkeyHandler.hpp"
#include <RandomEngine/API/Math/vec2.hpp>
#include <RandomEngine/API/GlobalData.hpp>
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include <RandomEngine/API/Auxiliary/print_vectors.hpp>
#include <RandomEngine/API/System/Mouse.hpp>

namespace game
{
	void HotkeyHandler::updateComponentsAlignment()
	{
	}
	void HotkeyHandler::handleEvents(const sf::Event& e)
	{
		auto& gdata = GlobalData::getInstance();
		switch (e.type)
		{
		case sf::Event::MouseButtonPressed:
			if (e.mouseButton.button == sf::Mouse::Left)
				is_pressed = true;
			break;
		case sf::Event::MouseButtonReleased:
			if (e.mouseButton.button == sf::Mouse::Left)
				is_pressed = false;
			break;
		case sf::Event::MouseMoved:
			ivec2 mouse_pos = { e.mouseMove.x, e.mouseMove.y };
			if (is_pressed)
			{
				ivec2 mouse_offset = prev_mouse_pos - mouse_pos;
				vec2 offset = Mouse::getOffset(gdata.camera.getNativeSize(), mouse_offset);
				gdata.camera.move(offset);
			}
			prev_mouse_pos = mouse_pos;
			break;
		}
		/*vec2 cur_pos = Mouse::getPosition();
		if (is_pressed)
		{
			vec2 offset = prev_mouse_pos - cur_pos;
			PRINT(offset);

			GlobalData::getInstance().camera.move(offset);
		}
		prev_mouse_pos = cur_pos;*/
		/*const ivec2 input = sf::Mouse::getPosition(gdata.window);
		const vec2 cur_pos(input.x, -input.y);
		if (is_pressed)
		{
			const vec2 offset = prev_mouse_pos - cur_pos;

			gdata.camera.move(offset * gdata.camera.getSize() * 0.001f);
		}*/

		//prev_mouse_pos = cur_pos;
	}
	void HotkeyHandler::update(float delta)
	{
	}
	void HotkeyHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
	}
}