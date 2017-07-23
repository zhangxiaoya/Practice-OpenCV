#include <iostream>
#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>

void SnapShow(const cv::Mat& img, const char* winname)
{
	cv::namedWindow(winname);
	imshow(winname, img);
	cv::waitKey(0);
	cv::destroyWindow(winname);
}

void DoCloseMorpholgyOperation(const cv::Mat& img)
{
	cv::Mat closedImg;
	auto element = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(1, 1));
	morphologyEx(img, closedImg, CV_MOP_CLOSE, element);
	SnapShow(closedImg, "Closed Image");
}

int main(int argc, char* argv[])
{
	auto img = cv::imread("..\\data\\lena.png");
	if(img.empty())
	{
		std::cout << "Read Image File Failed!" << std::endl;;
		system("Pause");
		return -1;
	}
	SnapShow(img, "Original Image");

	DoCloseMorpholgyOperation(img);

	system("Pause");
	return 0;
}
