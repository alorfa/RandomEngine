#pragma once

#define RENGINE_DEBUG

#ifdef RENGINE_DEBUG

#include <iostream>

#define PRINT(value) std::cout << #value " = " << value << std::endl
#define PRINTR(value) std::cout << "\r" #value " = " << (value) << "                "

#else

#define PRINT(value)
#define PRINTR(value) 

#endif //RENGINE_DEBUG