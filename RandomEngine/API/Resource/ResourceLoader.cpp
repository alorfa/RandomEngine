#include "ResourceLoader.hpp"

namespace random_engine
{
	std::map<std::filesystem::path, Resource*> ResourceLoader::resources = {};

	Resource& ResourceLoader::defaultLoad(const std::filesystem::path& path, int flags)
	{
		// if resource is already loaded
		Resource* res = resources[path];
		if (res)
			return *res;

		// else load
		res = loadFromFile(path, flags);
		if (res) 
		{
			// and add new resource in the map
			resources[path] = res;
			return *res;
		}

		// if loading is failed, return default resource
		return getDefault();
	}
	Resource& ResourceLoader::load(const std::filesystem::path& path, int flags)
	{
		return defaultLoad(path, flags);
	}
}