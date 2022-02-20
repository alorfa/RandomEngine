#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <filesystem>
#include "RandomEngine/API/Graphics/Camera.hpp"
#include "RandomEngine/API/Scene.hpp"

namespace random_engine
{
	struct GlobalData
	{
	private:
		GlobalData();
	public:
		sf::RenderWindow window;
		Camera camera;

		static GlobalData& getInstance();
	};

	extern std::filesystem::path res, user;
}