#pragma once

#include <SFML/Graphics/Shader.hpp>

namespace random_engine
{
	class DefaultShaders
	{
	public:
		static sf::Shader* getSpriteShader();
	};
}