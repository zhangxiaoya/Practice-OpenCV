#pragma once
#include <core/core.hpp>

struct DilationData
{
	DilationData() : dilationElem(0), dilationSize(0)
	{
	}

	int dilationElem;
	int dilationSize;
	cv::Mat srcImg;
};
