#pragma once
#include <Windows.h>

namespace util
{
#define CheckPerf(call, message)                                                                              \
{                                                                                                             \
	LARGE_INTEGER t1, t2, tc;                                                                                 \
	QueryPerformanceFrequency(&tc);                                                                           \
	QueryPerformanceCounter(&t1);                                                                             \
	call;                                                                                                     \
	QueryPerformanceCounter(&t2);                                                                             \
	printf("The Method Of %40s Use Time:%f\n", message, (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart);       \
};
}

