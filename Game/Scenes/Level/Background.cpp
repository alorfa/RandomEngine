#include "Background.hpp"
#include <RandomEngine/API/GlobalData.hpp>

namespace game
{
	void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		auto& global_data = GlobalData::getInstance();
		const vec2 size = global_data.camera.getNativeSize();
		const vec2& cam_pos = global_data.camera.getPosition();
		vec2 min = { cam_pos.x * 0.25f - size.x, cam_pos.y * 0.25f - size.y + 1.f };
		vec2 max = { cam_pos.x * 0.25f + size.x, cam_pos.y * 0.25f + size.y + 1.f };

		sprite.setPosition(cam_pos);

		sprite.setScale(size);
		sprite.setArea(min / SIZE, max / SIZE);

		target.draw(sprite);
	}
	void Background::setTexture(const Texture& t)
	{
		sprite.setTexture(t);
	}
	void Background::moveByTrigger(const fvec2& offset)
	{
		pos += offset;
	}
}