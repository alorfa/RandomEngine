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
		//bool loadFromFile(const std::string& filename, const sf::IntRect& area = sf::IntRect()) = delete;
	};
	class TextureLoader : public ResourceLoader
	{
	protected:
		Texture* loadFromFile(const std::filesystem::path& path, int flags = Texture::Default) override;
	public:
		Texture& getDefault() const override;

		Texture& load(const std::filesystem::path& path, int flags = Texture::Default) override;
	};
	extern TextureLoader textureLoader;
}