#pragma once

#include "Assert.hpp"
#include "RandomEngine/API/Graphics/Shape.hpp"

namespace random_engine
{
	void getShapeCount_Tests()
	{
		Assert::reset("Shape::getShapeCount");

		ASSERT_ARE_EQUAL(Shape::getShapeCount(0, sf::Points), 0, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(1, sf::Points), 1, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(6, sf::Points), 6, __LINE__);

		ASSERT_ARE_EQUAL(Shape::getShapeCount(0, sf::Lines), 0, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(1, sf::Lines), 0, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(6, sf::Lines), 3, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(7, sf::Lines), 3, __LINE__);

		ASSERT_ARE_EQUAL(Shape::getShapeCount(0, sf::Triangles), 0, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(1, sf::Triangles), 0, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(2, sf::Triangles), 0, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(3, sf::Triangles), 1, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(8, sf::Triangles), 2, __LINE__);

		ASSERT_ARE_EQUAL(Shape::getShapeCount(0, sf::Quads), 0, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(1, sf::Quads), 0, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(2, sf::Quads), 0, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(3, sf::Quads), 0, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(4, sf::Quads), 1, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(7, sf::Quads), 1, __LINE__);

		ASSERT_ARE_EQUAL(Shape::getShapeCount(0, sf::LineStrip), 0, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(1, sf::LineStrip), 0, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(2, sf::LineStrip), 1, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(7, sf::LineStrip), 6, __LINE__);

		ASSERT_ARE_EQUAL(Shape::getShapeCount(0, sf::TriangleStrip), 0, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(1, sf::TriangleStrip), 0, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(2, sf::TriangleStrip), 0, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(3, sf::TriangleStrip), 1, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getShapeCount(5, sf::TriangleStrip), 3, __LINE__);
	}

	void getVertexCount_Tests()
	{
		Assert::reset("Shape::getVertexCount");

		ASSERT_ARE_EQUAL(Shape::getVertexCount(0, sf::Points), 0, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getVertexCount(1, sf::Points), 1, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getVertexCount(2, sf::Points), 2, __LINE__);

		ASSERT_ARE_EQUAL(Shape::getVertexCount(0, sf::Lines), 0, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getVertexCount(1, sf::Lines), 2, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getVertexCount(2, sf::Lines), 4, __LINE__);

		ASSERT_ARE_EQUAL(Shape::getVertexCount(2, sf::Triangles), 6, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getVertexCount(2, sf::Quads), 8, __LINE__);

		ASSERT_ARE_EQUAL(Shape::getVertexCount(0, sf::LineStrip), 0, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getVertexCount(1, sf::LineStrip), 2, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getVertexCount(2, sf::LineStrip), 3, __LINE__);

		ASSERT_ARE_EQUAL(Shape::getVertexCount(0, sf::TriangleFan), 0, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getVertexCount(1, sf::TriangleFan), 3, __LINE__);
		ASSERT_ARE_EQUAL(Shape::getVertexCount(2, sf::TriangleFan), 4, __LINE__);
	}

	void shape_Tests()
	{
		getShapeCount_Tests();
		getVertexCount_Tests();
	}
}