#include <iostream>
#include <core/core.hpp>
#include <photo/photo.hpp>
#include <highgui.h>
#include <contrib/contrib.hpp>

int thresholdValue = 0;
int thresholdType = 3;
int const maxValue = 255;
int const maxType = 4;
int const maxBinaryValue = 255;

cv::Mat srcImg;
cv::Mat dstImg;
cv::Mat srcGray;
char* WindowName = "Threshold Demo";

char* trackerbarTypeName = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
char* trackerbarValueName = "Value";

void ThresholdDemo(int, void*)
{
	/* 0: Binary
	1: Binary Inverted
	2: Threshold Truncated
	3: Threshold to Zero
	4: Threshold to Zero Inverted
	*/
	cv::threshold(srcGray, dstImg, thresholdValue, maxBinaryValue, thresholdType);
	cv::imshow(WindowName, dstImg);
}

int main(int argc, char* argv[])
{
	srcImg = cv::imread("..\\..\\data\\lena.png");
	if(srcImg.empty() == true)
	{
		printf("Cannot open image file\n");
		system("Pause");
		return -1;
	}

	cv::cvtColor(srcImg, srcGray, CV_RGB2GRAY);
	cv::namedWindow(WindowName);

	cv::createTrackbar(trackerbarTypeName, WindowName, &thresholdType, maxType, ThresholdDemo);

	cv::createTrackbar(trackerbarValueName, WindowName, &thresholdValue, maxValue, ThresholdDemo);

	ThresholdDemo(0, 0);

	while(true)
	{
		int key = cv::waitKey(10);
		if(key == 27)
			break;
	}
	return 0;
}
