#pragma once

#include "ResourceLoader.hpp"
#include <SFML/Audio.hpp>

namespace random_engine
{
	class Sound : public Resource, public sf::SoundBuffer
	{
	};

	class SoundLoader : public ResourceLoader
	{
	public:
		Sound* loadFromFile(const std::filesystem::path& path, int flags = 0) override;

		Sound& getDefault() const override;

		Sound& load(const std::filesystem::path& path, int flags = 0) override;
	};
	extern SoundLoader soundLoader; 
}