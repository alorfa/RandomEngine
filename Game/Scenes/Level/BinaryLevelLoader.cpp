#include "BinaryLevelLoader.hpp"
#include <fstream>
#include "Game/Scenes/Level.hpp"
#include "Game/Scenes/Editor/DevLevel.hpp"
#include "Serializer.hpp"
#include <RandomEngine/API/Auxiliary/DEBUG.hpp>
#include <RandomEngine/API/Auxiliary/print_vectors.hpp>

namespace game
{
	LevelState& BinaryLevelLoader::getDefault() const
	{
		static LevelState state;
		return state;
	}
	LevelState* BinaryLevelLoader::loadFromFile(const std::filesystem::path& path, int flags)
	{
		Serializer ser(path, Serializer::Read);

		LevelState* result = new LevelState;

		ser.readFromBytes(result->bg_pos);
		ser.readFromBytes(result->bottom_ground);
		ser.readFromBytes(result->top_ground);
		const size_t count = ser.readFromBytes<int>();
		for (size_t i = 0; i < count; i++)
		{
			result->objects.push_back(ser.readObject());
		}

		return result;
	}
	LevelState& BinaryLevelLoader::load(const std::filesystem::path& path, int flags)
	{
		return static_cast<LevelState&>(defaultLoad(path, flags));
	}
	void BinaryLevelLoader::saveToFile(const std::filesystem::path& path, const DevLevel& level)
	{
		Serializer ser(path, Serializer::Write);

		ser.writeAsBytes(level.level->bg.pos);
		ser.writeAsBytes(level.level->bottom.pos);
		ser.writeAsBytes(level.level->top.pos);
		i32 size = 0;
		for (const auto& part : level.getParts())
		{
			for (const auto& obj : *part.second)
				size++;
		}
		ser.writeAsBytes(size);
		for (const auto& part : level.getParts())
		{
			for (const auto& obj : *part.second)
			{
				ser.writeObject(*obj);
			}
		}
	}
	BinaryLevelLoader binaryLevelLoader;
}