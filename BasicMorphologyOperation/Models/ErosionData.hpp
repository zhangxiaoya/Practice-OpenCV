#pragma once
#include <core/core.hpp>

struct ErosionData
{
	ErosionData() : erosionElem(0), erosionSize(0)
	{
	}
	cv::Mat srcImg;
	int erosionElem;
	int erosionSize;
};
