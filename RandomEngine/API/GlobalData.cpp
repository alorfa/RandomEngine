#include "GlobalData.hpp"

namespace random_engine
{
	GlobalData::GlobalData()
		: camera(window)
	{
		
	}
	GlobalData& GlobalData::getInstance()
	{
		static GlobalData* instance = new GlobalData;
		return *instance;
	}
}