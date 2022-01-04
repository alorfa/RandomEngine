#pragma once

#include <Game/Object.hpp>
#include <RandomEngine/API/Graphics/Sprite.hpp>
#include <RandomEngine/API/Math/CollisionFunctions.hpp>

using namespace random_engine;

namespace game
{
	class SpriteObject : public game::Object
	{
		mutable Sprite sprite;
		mutable PhysicalRect physical_rect;
		mutable sf::Vertex hitbox_vertices[5];

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		Rect hitbox;
		SpriteObject();

		bool touches(const Player&) const override;
		RepulsionResult getRepulsionVector(const Player&) const override;

		void load(const std::filesystem::path& path);
		void setArea(const vec2& p1, const vec2& p2);

		const PhysicalRect& getPhysicalRect() const;
		Rect getCollisionRect() const;
	};
}