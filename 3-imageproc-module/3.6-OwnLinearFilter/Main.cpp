#include <iostream>
#include <core/core.hpp>
#include <highgui.h>
#include <video/video.hpp>

int main(int argc, char* argv[])
{
	cv::Mat srcImg = cv::imread("..\\..\\data\\lena.png");
	cv::Mat dstImg;

	if(srcImg.empty() == true)
	{
		printf("Cannot open image file\n");
		system("Pause");
		return -1;
	}

	int kernelSize = 3;
	int step = 0;

	while (true)
	{
		int key = cv::waitKey(500);
		if(key == 27)
			break;

		kernelSize = kernelSize + 2 * (step % 5);

		cv::Mat kernel = cv::Mat::ones(kernelSize, kernelSize, CV_32F) / static_cast<float>(kernelSize * kernelSize);
		 
		cv::filter2D(srcImg, dstImg, -1, kernel);
		cv::imshow("Own Linear Filter", dstImg);
		step++;
	}
	return 0;
}
