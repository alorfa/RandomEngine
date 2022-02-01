#pragma once

#include <Game/Object.hpp>
#include <RandomEngine/API/Graphics/Sprite.hpp>
#include <RandomEngine/API/Math/CollisionFunctions.hpp>
#include <filesystem>

using namespace random_engine;

namespace game
{
	class SpriteObject : public game::Object
	{
		static sf::Shader* select_shader;

		mutable Sprite sprite;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		SpriteObject();

		bool touches(const PhysicalRect&) const override;
		RepulsionResult getRepulsionVector(const PhysicalRect&) const override;

		void load(const std::filesystem::path& path);
		void setArea(const vec2& p1, const vec2& p2);

		const PhysicalRect& getPhysicalRect() const;
		Rect getCollisionRect() const;

		std::unique_ptr<Object> clone() const override;
	};
}