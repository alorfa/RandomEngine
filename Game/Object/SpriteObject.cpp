#include "SpriteObject.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "SpriteObject.hpp"

#include "Game/Player.hpp"
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include <RandomEngine/API/Auxiliary/print_vectors.hpp>



namespace game
{
	namespace
	{
		SpriteObject::RepulsionResult handleRects(const vec2& p1, const vec2& p2,
			const vec2& r1, const vec2& r2, const vec2& p_pos, const vec2& obj_pos)
		{
			SpriteObject::RepulsionResult result;
			result.touches = (p2.x >= r1.x &&
				p1.x <= r2.x &&
				p2.y >= r1.y &&
				p1.y <= r2.y);
			if (result.touches)
				result.direction.y = p_pos.y - obj_pos.y ;
			return result;
		}
	}
	void SpriteObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		sprite.setPosition(getPosition());

		target.draw(sprite);
	}
	bool SpriteObject::touches(const Player& p) const
	{
		const vec2 p1 = p.getPosition() - p.getScale() * 0.5f;
		const vec2 p2 = p1 + p.getScale();

		const vec2 r1 = getPosition() - getScale() * 0.5f;
		const vec2 r2 = r1 + getScale();

		return handleRects(p1, p2, r1, r2, p.getPosition(), getPosition()).touches;
	}
	SpriteObject::RepulsionResult SpriteObject::getRepulsionVector(const Player& p) const
	{
		RepulsionResult result;
		const vec2 p1 = p.getPosition() - p.getScale() * 0.5f;
		const vec2 p2 = p1 + p.getScale();

		const vec2 r1 = getPosition() - getScale() * 0.5f;
		const vec2 r2 = r1 + getScale();

		return// handleRects(p1, p2, r1, r2, p.getPosition(), getPosition());
			result;
	}
	void SpriteObject::load(const std::filesystem::path& path)
	{
		sprite.setTexture(textureLoader.load(path));
	}
}