#pragma once

#include <map>
#include <filesystem>

namespace random_engine
{
	class Resource
	{

	};
	class ResourceLoader
	{
		static std::map<std::filesystem::path, Resource*> resources;
	protected:
		virtual Resource* loadFromFile(const std::filesystem::path& path, int flags) = 0;

		Resource& defaultLoad(const std::filesystem::path& path, int flags = 0);
	public:
		virtual Resource& getDefault() const = 0;

		virtual Resource& load(const std::filesystem::path& path, int flags = 0);
	};
}