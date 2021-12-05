#include "LevelLoader.hpp"
#include <RandomEngine/API/Resource/File.hpp>
//#include <boost/json.hpp>
//#include <boost/json/basic_parser_impl.hpp>

//using namespace boost::json;

namespace game
{
	LevelState* LevelLoader::loadFromFile(const std::filesystem::path& path, int flags)
	{
		/*std::string json_data = File::readTextAsString(path);
		parse_options options;
		options.allow_comments = true;
		error_code err;
		value json = parse(json_data, err, {}, options);*/

		return nullptr;
	}
	LevelState& LevelLoader::getDefault() const
	{
		static LevelState defaultLevel;
		return defaultLevel;
	}
	LevelState& LevelLoader::load(const std::filesystem::path& path, int flags)
	{
		return static_cast<LevelState&>(defaultLoad(path, flags));
	}
}