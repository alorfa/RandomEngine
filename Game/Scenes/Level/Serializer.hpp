#pragma once

#include <fstream>
#include <map>
#include <RandomEngine/API/Math/CollisionFunctions.hpp>

using namespace random_engine;

namespace game
{
	class Object;

	class Serializer
	{
		std::fstream stream;

		void move(int bytes_offset);
	public:

		enum FileMode
		{
			Read, Write
		};

		Serializer(const std::filesystem::path& path, FileMode mode);

		template <typename T>
		void writeAsBytes(const T& obj)
		{
			stream.write((const char*)&obj, sizeof(T));
		}
		void writeString(const std::string_view string);
		void writeObject(const game::Object& obj);

		template <typename T>
		void readFromBytes(T& out)
		{
			stream.read((char*)&out, sizeof(T));
		}
		void readString(std::string& out);

		template <typename T>
		T readFromBytes()
		{
			T result;
			stream.read((char*)&result, sizeof(T));
			return result;
		}
		std::string readString();
		std::unique_ptr<Object> readObject();
	};
}