// CXL - A programming language
// This file is licensed under the BSD-2 Clause license.

#ifdef _MSC_VER
#define COMPILER MSVC
#endif
#ifdef __clang__
#define COMPILER CLANG
#endif

#ifdef __GNUC__
#ifndef __clang__
#define COMPILER GCC
#endif
#endif

#ifdef _WIN32
#ifdef _WIN64
#define X64
#else
#define X86
#endif
#else
#ifdef __LP64__
#define X64
#else
#define X86
#endif
#endif


