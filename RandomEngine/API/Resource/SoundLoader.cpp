#include "SoundLoader.hpp"

namespace random_engine
{
	Sound* SoundLoader::loadFromFile(const std::filesystem::path& path, int flags)
	{
		Sound* result = new Sound;
		if (not result->loadFromFile(path.generic_u8string()))
		{
			delete result;
			return nullptr;
		}
		return result;
	}
	Sound& SoundLoader::getDefault() const
	{
		static Sound* sound = new Sound;
		return *sound;
	}
	Sound& SoundLoader::load(const std::filesystem::path& path, int flags)
	{
		return static_cast<Sound&>(defaultLoad(path, flags));
	}

	SoundLoader soundLoader;
}