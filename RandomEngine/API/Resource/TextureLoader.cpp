#include "TextureLoader.hpp"

namespace random_engine
{
	Texture* TextureLoader::loadFromFile(const std::filesystem::path& path, int flags)
	{
		sf::Image img;
		if (not img.loadFromFile(path.generic_u8string()))
			return nullptr;

		img.flipVertically();
		Texture* result = new Texture();
		if (not result->loadFromImage(img))
		{
			delete result;
			return nullptr;
		}
		if (flags == 0)
			flags = Texture::Default;
		result->setSmooth(flags & Texture::Smooth);
		result->setRepeated(flags & Texture::Repeated);
		if (flags & Texture::Mipmaps)
			result->generateMipmap();
		return result;
	}
	Resource& TextureLoader::getDefault() const
	{
		static Texture* t = new Texture;
		return *t;
	}
	Texture& TextureLoader::load(const std::filesystem::path& path, int flags)
	{
		return static_cast<Texture&>(defaultLoad(path, flags));
	}
	TextureLoader textureLoader;
}