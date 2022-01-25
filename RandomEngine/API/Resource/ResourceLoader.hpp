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
		Resource& defaultLoad(const std::filesystem::path& path, int flags = 0);
	public:
		virtual Resource* loadFromFile(const std::filesystem::path& path, int flags) = 0;

		virtual Resource& getDefault() const = 0;

		virtual Resource& load(const std::filesystem::path& path, int flags = 0) = 0;

		virtual ~ResourceLoader() = default;
	};
}