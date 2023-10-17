#pragma once
// Unsigned int types
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

// Signed int types
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

// Floating point types
typedef float f32;
typedef double f64;

// Boolean types
typedef int b32;
typedef char b8;

// TRUE / FALSE definition
#define TRUE 1
#define FALSE 0

// Platform detection
#if defined(WIN32)||defined(_WIN32)||defined(__WIN32__)
#define PO_PLATFORM_WINDOWS 1
	#ifndef _WIN64
	#error "64-bit is required on Windows"
	#endif
#else
#error "Pocket game engine only works on Windows!"
#endif
