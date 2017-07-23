#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include <iostream>
#include <contrib/contrib.hpp>

const int MAX_KERNEL_LENGTH = 31;

void SnapShow(const cv::Mat& img, const char* winname, int delay = 0)
{
	cv::namedWindow(winname);
	imshow(winname, img);
	cv::waitKey(delay);
	cv::destroyWindow(winname);
}

void DoBlurSmooth(cv::Mat& img)
{
	auto delay = 500;
	cv::Mat bluredImg;

	std::string titleFormat = "Blured image with kernel size %d";
	const auto titleBufferSize = 100;
	char fullTitle[titleBufferSize];

	for (auto i = 1; i < MAX_KERNEL_LENGTH; ++i)
	{
		blur(img, bluredImg, cv::Size(i, i), cv::Point(-1, -1));
		sprintf_s(fullTitle, titleBufferSize, titleFormat.c_str(), i);
		SnapShow(bluredImg, fullTitle, delay);
	}
}

int main(int argc, char* argv[])
{
	auto img = cv::imread("..\\data\\lena.png");
	if (img.empty())
	{
		std::cout << "Read Image File Failed!" << std::endl;
		system("Pause");
		return -1;
	}
	SnapShow(img, "Original Image");

	DoBlurSmooth(img);

	cv::destroyAllWindows();
	system("Pause");
	return 0;
}
