#pragma once

#include <stdint.h>

namespace random_engine
{
	typedef int64_t int64, i64;
	typedef int32_t int32, i32;
	typedef int16_t int16, i16;
	typedef int8_t  int8,  i8, sbyte;

	typedef uint64_t uint64, u64;
	typedef uint32_t uint32, u32;
	typedef uint16_t uint16, u16;
	typedef uint8_t  uint8,  u8, ubyte;

	typedef float f32;
	typedef double f64;

	//float value, which must be from 0 to 1
	typedef float float01;
}