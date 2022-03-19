#pragma once

#include <fstream>
#include <map>
#include <RandomEngine/API/Math/CollisionFunctions.hpp>

using namespace random_engine;

namespace game
{
	class SpriteObject;
	class VertexObject;
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
		void writeObjectInfo(const Object& object, const vec2& size, const Rect& hitbox);
		void writeSpriteObject(const SpriteObject& object);
		void writeVertexObject(const VertexObject& object);
		void writeObject(const Object& object);

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
		void readObjectInfo(Object& object);
		std::unique_ptr<SpriteObject> readSpriteObject();
		std::unique_ptr<VertexObject> readVertexObject();
		std::unique_ptr<Object> readObject();
	};
}