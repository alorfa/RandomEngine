#include "Serializer.hpp"
#include <filesystem>
#include <RandomEngine/API/Resource/TextureLoader.hpp>
#include <RandomEngine/API/GlobalData.hpp>
#include "Game/Object.hpp"
#include "Game/Object/SpriteObject.hpp"
#include "Game/Object/VertexObject.hpp"
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
		writeAsBytes((int32)string.size());
		stream.write(string.data(), string.size());
	}

	void Serializer::writeObjectInfo(const Object& object, const vec2& size, const Rect& hitbox)
	{
		// transform
		writeAsBytes(object.getPosition());
		writeAsBytes(object.getRotation());
		if (object.getScale() != size)
		{
			writeAsBytes('s');
			writeAsBytes(object.getScale());
		}

		// collision info
		if (object.hitbox != hitbox)
		{
			writeAsBytes('h');
			writeAsBytes(object.hitbox);
		}
		writeAsBytes((int8)object.collisionMode);
		if (object.collisionMode == StaticBody::OnClick or
			object.collisionMode == StaticBody::Touch)
		{
			if (object.action == ObjectActions::die)
				writeAsBytes((int8)1);
			if (object.action == ObjectActions::normalJump)
				writeAsBytes((int8)2);
			if (object.action == ObjectActions::littleJump)
				writeAsBytes((int8)3);
			if (object.action == ObjectActions::toShip)
				writeAsBytes((int8)4);
			if (object.action == ObjectActions::toCube)
				writeAsBytes((int8)5);
		}
	}

	void Serializer::writeSpriteObject(const SpriteObject& object)
	{
		writeAsBytes('s');
		const auto& info = SpriteObjectBuilder::id_map.at(object.getId());

		writeAsBytes((int16)object.getId());

		writeObjectInfo(object, info.size, info.hitbox);
	}
	void Serializer::writeVertexObject(const VertexObject& obj)
	{
		writeAsBytes('v');
		writeAsBytes((uint8)obj.drawMode);
		const uint32 vert_count = obj.vertices.size();
		writeAsBytes(vert_count);
		for (int i = 0; i < vert_count; i++)
		{
			writeAsBytes(obj.vertices[i].position);
			writeAsBytes(obj.vertices[i].color);
		}
	}
	void Serializer::writeObject(const Object& obj)
	{
		if (dynamic_cast<const SpriteObject*>(&obj))
		{
			writeSpriteObject(dynamic_cast<const SpriteObject&>(obj));
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
	void Serializer::readObjectInfo(Object& object)
	{
		// transform
		object.setPosition(readFromBytes<vec2>());
		object.setRotation(readFromBytes<float>());
		if (readFromBytes<char>() == 's')
			object.setScale(readFromBytes<vec2>());
		else
			move(-1);

		// collision info
		if (readFromBytes<char>() == 'h')
			readFromBytes(object.hitbox);
		else
			move(-1);

		object.collisionMode = (StaticBody::CollisionMode)readFromBytes<int8>();
		if (object.collisionMode == StaticBody::OnClick or
			object.collisionMode == StaticBody::Touch)
		{
			object.action = SpriteObjectBuilder::idToAction(readFromBytes<int8>());
		}
	}
	std::unique_ptr<SpriteObject> Serializer::readSpriteObject()
	{
		auto result = spriteObjectBuilder.build(readFromBytes<int16>());

		readObjectInfo(*result);
		
		return result;
	}
	std::unique_ptr<VertexObject> Serializer::readVertexObject()
	{
		const uint8 drawMode = readFromBytes<uint8>();
		auto result = std::make_unique<VertexObject>((sf::PrimitiveType)drawMode);
		const uint32 vert_count = readFromBytes<uint32>();
		result->vertices.resize(vert_count);
		for (uint32 i = 0; i < vert_count; i++)
		{
			readFromBytes<sf::Vector2f>(result->vertices[i].position);
			readFromBytes<sf::Color>(result->vertices[i].color);
		}
		return result;
	}
	std::unique_ptr<Object> Serializer::readObject()
	{
		const char objectType = readFromBytes<char>();
		if (objectType == 's')
		{
			return readSpriteObject();
		}
		if (objectType == 'v')
		{
			return readVertexObject();
		}
	}
}