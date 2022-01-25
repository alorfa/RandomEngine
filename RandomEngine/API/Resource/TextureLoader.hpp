#pragma once

#include "ResourceLoader.hpp"
#include <SFML/Graphics/Texture.hpp>

namespace random_engine
{
	class Texture : public Resource, public sf::Texture
	{
	public:
		enum Flags
		{
			Smooth = 1,
			Repeated = 2,
			Mipmaps = 4,
			Default = Smooth | Repeated | Mipmaps
		};
	};
	class TextureLoader : public ResourceLoader
	{
	public:
		Texture* loadFromFile(const std::filesystem::path& path, int flags = Texture::Default) override;

		Texture& getDefault() const override;

		Texture& load(const std::filesystem::path& path, int flags = Texture::Default) override;
	};
	extern TextureLoader textureLoader;
}