#include "File.hpp"
#include <RandomEngine/API/System/types.hpp>

namespace random_engine
{
	size_t File::getSize()
	{
		if (not isOpen())
			return 0;

		file.seekg(0, file.end);
		size_t result = file.tellg();
		file.seekg(0, file.beg);

		return result;
	}
	File::File(const std::filesystem::path& path, int flag)
	{
		open(path, flag);
	}
	File& File::open(const std::filesystem::path& path, int flag)
	{
		close();

		if (not std::filesystem::exists(path))
			return *this;

		u32 std_flag = 0;
		if (flag & Flag::Read)
			std_flag |= std::ios_base::in;
		if (flag & Flag::Write)
			std_flag |= std::ios_base::out;
		if (flag & Flag::Add)
			std_flag |= std::ios_base::app;
		if (flag & Flag::Text)
			text_mode = true;
		else
			std_flag |= std::ios_base::binary;

		file.open(path, std_flag);
		if (not file.is_open())
			return *this;

		open_path = &path;
		return *this;
	}
	bool File::isOpen() const
	{
		return file.is_open();
	}
	File& File::close()
	{
		if (file.is_open())
			file.close();
		return *this;
	}
	std::string File::readTextAsString(const std::filesystem::path& path)
	{
		std::string result;

		File file;
		file.open(path, File::Read | File::Text);
		int ch = 0;
		while ((ch = file.file.get()) != EOF)
			result += ch;

		return result;
	}
}