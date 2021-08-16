#include "Circle.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <RandomEngine/API/Math/Trig.hpp>

namespace random_engine
{
	void Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (verticies.getVertexCount() > 2)
		{
			states.transform.translate(getPosition()).scale(getScale());
			target.draw(verticies, states);
		}
	}
	void Circle::create(int vert_count, const vec2& size)
	{
		this->vertex_count = vert_count;

		verticies.resize(vert_count);
		for (size_t i = 0; i < vert_count; i++)
			verticies[i] = Trig::getCirclePoint(i * (Trig::TAU / vert_count), size * 0.5f);
		verticies.setPrimitiveType(sf::PrimitiveType::TrianglesFan);
	}
	Circle::Circle(int vert_count, const vec2& size)
	{
		create(vert_count, size);
	}
}