#pragma once

#include <string>
#include <iostream>

namespace random_engine
{
	class Assert
	{
	public:
		inline static size_t errCount = 0;
		inline static std::string testMethod = "";

		inline static void reset(const std::string& testedMethod)
		{
			errCount = 0;
			testMethod = testedMethod;
		}
		inline static std::ostream& errorMessage(int line)
		{
			errCount++;
			std::cout << "In " << testMethod << " in line " << line << ": ";
			return std::cout;
		}
	};
}

using namespace random_engine;

#define ASSERT_ARE_EQUAL(v1, v2, line)					\
	if (v1 != v2) 										\
		Assert::errorMessage(line) << #v1 " == " << v1 << ", expected " #v2 << std::endl;

#define ASSERT_IS_TRUE(conditional, line)				\
	if (not conditional) 								\
		Assert::errorMessage(line) << #conditional " is false" << std::endl;