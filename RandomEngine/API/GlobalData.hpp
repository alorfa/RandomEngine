#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <filesystem>
#include "RandomEngine/API/Graphics/Camera.hpp"
#include "RandomEngine/API/Scene.hpp"

namespace random_engine
{
	struct GlobalData
	{
		GlobalData();
	public:
		sf::RenderWindow window;
		std::filesystem::path res;
		Camera camera;

		static GlobalData& getInstance();
	};
}