#pragma once

#include <RandomEngine/API/Math/vec2.hpp>

using namespace random_engine;

namespace game
{
	class IMoveableObject
	{
	public:
		virtual void moveByTrigger(const vec2& offset) = 0;
	};

	class IRotatableObject
	{
	public:
		virtual void rotateByTrigger(float deg) = 0;
	};

	class IScalableObject
	{
	public:
		virtual void scaleByTrigger(const vec2& factor) = 0;
	};

	class ITransformableObject : public IMoveableObject, public IRotatableObject, public IScalableObject
	{
	};
}