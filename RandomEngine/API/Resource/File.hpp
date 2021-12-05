#pragma once

#include <vector>
#include <filesystem>
#include <RandomEngine/API/System/types.hpp>
#include <fstream>

namespace random_engine
{
	class File
	{
		std::fstream file;
		const std::filesystem::path* open_path = nullptr;
		bool text_mode = false;

		size_t getSize();
	public:
		File() = default;
		File(const File&) = delete;
		File& operator=(const File&) = delete;
		~File() = default;

		enum Flag : int
		{
			Read = 1 << 0,
			Write = 1 << 1,
			Add = 1 << 2,
			Text = 1 << 3
		};
		File(const std::filesystem::path& path, int flag = Flag::Read);
		File& open(const std::filesystem::path& path, int flag = Flag::Read);
		bool isOpen() const;
		File& close();

		template <typename T>
		void read(T* out, size_t size)
		{
			file.read((char*)out, size);
		}

		template <typename T>
		static std::vector<T> readAllBytes(const std::filesystem::path& path)
		{
			std::vector<T> result;

			File file;
			size_t filesize = file.open(path, File::Read).getSize();
			if (not filesize)
				return result;

			result.resize(filesize);
			file.read(result.data(), filesize);
			return result;
		}
		static std::string readTextAsString(const std::filesystem::path& path);
	};
}