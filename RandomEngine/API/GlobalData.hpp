#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <filesystem>
#include "RandomEngine/API/Graphics/Camera.hpp"

namespace random_engine
{
	struct GlobalData
	{
	private:
		GlobalData();
	public:
		sf::RenderWindow window;
		std::filesystem::path res;
		Camera camera;

		static GlobalData& getInstance();
	};
}