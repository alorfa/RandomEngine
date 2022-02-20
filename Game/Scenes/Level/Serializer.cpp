#include "Serializer.hpp"
#include <filesystem>
#include <RandomEngine/API/Resource/TextureLoader.hpp>
#include <RandomEngine/API/GlobalData.hpp>
#include "Game/Object.hpp"
#include "Game/Object/SpriteObject.hpp"
#include "Game/Object/ObjectActions.hpp"
#include "Game/Object/SpriteObjectBuilder.hpp"

namespace game
{
	void Serializer::move(int bytes_offset)
	{
		size_t size = stream.tellg();
		stream.seekg(size + bytes_offset);
	}
	Serializer::Serializer(const std::filesystem::path& path, FileMode mode)
	{
		u32 nmode = std::ios_base::binary;
		if (mode == FileMode::Read)
			nmode |= std::ios_base::in;
		else
			nmode |= std::ios_base::out;
		stream.open(path, nmode);
	}
	void Serializer::writeString(const std::string_view string)
	{
		writeAsBytes((int)string.size());
		stream.write(string.data(), string.size());
	}
	void Serializer::writeObject(const game::Object& obj)
	{
		if (dynamic_cast<const SpriteObject*>(&obj))
		{
			writeAsBytes('s');
			const SpriteObject& object = dynamic_cast<const SpriteObject&>(obj);
			const auto& info = SpriteObjectBuilder::id_map.at(object.getId());

			// id
			writeAsBytes(object.getId());

			// transform
			writeAsBytes(object.getPosition());
			writeAsBytes(object.getRotation());
			if (object.getScale() != info.size)
			{
				writeAsBytes('s');
				writeAsBytes(object.getScale());
			}

			// collision info
			if (object.hitbox != info.hitbox)
			{
				writeAsBytes('h');
				writeAsBytes(object.hitbox);
			}
			writeAsBytes(object.collisionMode);
			if (object.collisionMode == StaticBody::OnClick or
				object.collisionMode == StaticBody::Touch)
			{
				if (object.action == ObjectActions::die)
					writeAsBytes(1);
				if (object.action == ObjectActions::normalJump)
					writeAsBytes(2);
				if (object.action == ObjectActions::littleJump)
					writeAsBytes(3);
				if (object.action == ObjectActions::toShip)
					writeAsBytes(4);
				if (object.action == ObjectActions::toCube)
					writeAsBytes(5);
			}
		}
	}
	void Serializer::readString(std::string& out)
	{
		const size_t size = readFromBytes<int>();
		stream.read(out.data(), size);
	}
	std::string Serializer::readString()
	{
		std::string result;
		const size_t size = readFromBytes<int>();
		stream.read(result.data(), size);
		return result;
	}
	std::unique_ptr<Object> Serializer::readObject()
	{
		const char objectType = readFromBytes<char>();
		if (objectType == 's')
		{
			SpriteObjectBuilder builder;
			builder.setObjectId(readFromBytes<int>());
			auto result = builder.build();

			// transform
			result->setPosition(readFromBytes<vec2>());
			result->setRotation(readFromBytes<float>());
			if (readFromBytes<char>() == 's')
				result->setScale(readFromBytes<vec2>());
			else
				move(-1);

			// collision info
			if (readFromBytes<char>() == 'h')
				readFromBytes(result->hitbox);
			else
				move(-1);

			readFromBytes(result->collisionMode);
			if (result->collisionMode == StaticBody::OnClick or
				result->collisionMode == StaticBody::Touch)
			{
				result->action = builder.idToAction(readFromBytes<int>());
			}
			return result;
		}
	}
}