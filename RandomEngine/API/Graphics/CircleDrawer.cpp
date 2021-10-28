#include "CircleDrawer.hpp"
#include <SFML/Graphics/Shader.hpp>
#include <vector>
#include "RandomEngine/API/Auxiliary/DEBUG.hpp"

namespace random_engine
{
	namespace
	{
		template <typename T>
		T clamp(T value, T min, T max)
		{
			if (value > max)
				return max;
			if (value < min)
				return min;
			return value;
		}

		std::vector<sf::VertexArray> circles;
		sf::Shader* getCircleShader(const color4f& center, const color4f& outer)
		{
			static const char* vsh = R"raw(
void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    // forward the vertex color
    gl_FrontColor = gl_Color;
})raw"; 
			static const char* fsh = R"raw(
void main()
{
    // multiply it by the color
    gl_FragColor = gl_Color * pixel;
})raw";
			static sf::Shader* shader = nullptr;
			if (not shader)
			{
				shader = new sf::Shader();
				shader->loadFromMemory(vsh, fsh);
			}
			shader->setUniform("center", sf::Glsl::Vec4(center.r, center.g, center.b, center.a));
			shader->setUniform("outer", sf::Glsl::Vec4(outer.r, outer.g, outer.b, outer.a));
			return shader;
		}
	}
	

	size_t CircleDrawer::computeVertexCount(const sf::Transformable& transform, 
		const sf::Transformable& camera, const States& states)
	{
		const float circleDetailing = transform.getScale().x / camera.getScale().x;
		size_t vertCount = size_t(circleDetailing * states.detailing);
		vertCount = clamp(vertCount, size_t(6), MAX_VERTICIES);

		return vertCount;
	}

	void CircleDrawer::draw(sf::RenderTarget& target,
		const sf::Transformable& transform, const sf::Transformable& camera, const States& states)
	{
		const size_t vertCount = computeVertexCount(transform, camera, states);

		const auto& circle = getCircle(vertCount);

		sf::RenderStates rstates;
		rstates.blendMode.alphaSrcFactor = sf::BlendMode::OneMinusSrcAlpha;
		rstates.transform = transform.getTransform();
		rstates.shader = getCircleShader(states.center, states.outer);
		target.draw(circle, rstates);
	}
	sf::VertexArray CircleDrawer::createCircle(size_t vert_count, const vec2& size)
	{
		/* additional point(with index 0) is the center of the circle
		* another additional point is a copy of the first circle point
		*/
		sf::VertexArray verticies(sf::TrianglesFan, vert_count + 2);
		verticies[0].position = { 0.f, 0.f };
		for (size_t i = 1; i < vert_count + 2; i++)
			verticies[i].position = Trig::getCirclePoint(i * (Trig::TAU / vert_count), size * 0.5f);
		return verticies;
	}
	const sf::VertexArray& CircleDrawer::getCircle(size_t vert_count)
	{
		vert_count = clamp(vert_count, size_t(6), MAX_VERTICIES);

		if (vert_count >= circles.size())
			circles.resize(vert_count + 1);

		auto& circle = circles[vert_count];
		if (circle.getVertexCount() == 0) 
		{
			circle = createCircle(vert_count);
			//DEBUGSTREAM << "Created circle " << vert_count << std::endl;
		}

		return circle;
	}
}