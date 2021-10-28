#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "RandomEngine/API/Graphics/Camera.hpp"
#include "RandomEngine/API/Math/color.hpp"
#include <SFML/Graphics/VertexArray.hpp>

namespace random_engine
{
	class CircleDrawer
	{
		inline static size_t appWindowSize = 0;
	public:
		static const size_t MAX_VERTICIES = 200;

		struct States
		{
			int vertCount = 0;
			float detailing = 0.f;
			color4f center, outer;
		};

		static void setAppWindowSize(size_t pixels);
		static size_t computeVertexCount(const sf::Transformable& transform, const sf::Transformable& camera,
			const States&);
		static void draw(sf::RenderTarget&,
			const sf::Transformable& transform, const sf::Transformable& camera, const States&);
		static sf::VertexArray createCircle(size_t vert_count, const vec2& size = { 1, 1 });
		static const sf::VertexArray& getCircle(size_t vert_count);
	};
}