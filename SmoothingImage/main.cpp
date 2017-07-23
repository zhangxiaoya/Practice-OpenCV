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

void DoBlurSmooth(const cv::Mat& img)
{
	std::cout << "Bulr is doing ..." << std::endl;
	auto delay = 500;
	cv::Mat bluredImg;

	std::string titleFormat = "Blured image with kernel size %d";
	const auto titleBufferSize = 100;
	char fullTitle[titleBufferSize];

	for (auto i = 1; i < MAX_KERNEL_LENGTH; i += 2)
	{
		blur(img, bluredImg, cv::Size(i, i), cv::Point(-1, -1));
		sprintf_s(fullTitle, titleBufferSize, titleFormat.c_str(), i);
		SnapShow(bluredImg, fullTitle, delay);
	}
	std::cout << "Blur is Done!"<<std::endl;
}

void DoGaussianBlur(const cv::Mat& img)
{
	std::cout << "Gaussian Blur is doing ..."<<std::endl;
	auto delay = 500;

	std::string titleFormat = "Gaussion Blured image with kernel size %d";
	const auto titleBufferSize = 100;
	char fullTitle[titleBufferSize];

	cv::Mat guassianBulredImg;
	for (auto i = 1; i < MAX_KERNEL_LENGTH; i += 2)
	{
		GaussianBlur(img, guassianBulredImg, cv::Size(i, i), 0, 0);
		sprintf_s(fullTitle, titleBufferSize, titleFormat.c_str(), i);
		SnapShow(guassianBulredImg, fullTitle, delay);
	}
	std::cout << "Gaussian Blur is Done!" << std::endl;
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

	DoGaussianBlur(img);

	cv::destroyAllWindows();
	system("Pause");
	return 0;
}
