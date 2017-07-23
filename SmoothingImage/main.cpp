#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include <iostream>
#include <contrib/contrib.hpp>
#include <core/affine.hpp>

const int MAX_KERNEL_LENGTH = 31;

void SnapShow(const cv::Mat& img, const char* winname)
{
	cv::namedWindow(winname);
	imshow(winname, img);
	cv::waitKey(0);
	cv::destroyWindow(winname);
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

	cv::Mat bluredImg;
	for (auto i = 1; i < MAX_KERNEL_LENGTH; ++i)
	{
		blur(img, bluredImg, cv::Size(i, i), cv::Point(-1, -1));
		SnapShow(bluredImg, "Blured Image");
	}

	cv::destroyAllWindows();
	system("Pause");
	return 0;
}
