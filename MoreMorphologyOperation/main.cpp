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

void MorphologyOperation(const cv::Mat& img, cv::Mat& destImg, int op)
{
	auto element = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(1, 1));
	morphologyEx(img, destImg, op, element);
}

void DoCloseMorpholgyOperation(const cv::Mat& img)
{
	cv::Mat closedImg;
	MorphologyOperation(img, closedImg, CV_MOP_CLOSE);
	SnapShow(closedImg, "Closed Image");
}

void DoOpenMorphologyOperation(const cv::Mat& img)
{
	cv::Mat openedImg;
	MorphologyOperation(img, openedImg, CV_MOP_OPEN);
	SnapShow(openedImg, "Opened Image");
}

void DoGradientMorphologyOperation(const cv::Mat& img)
{
	cv::Mat gradientImg;
	MorphologyOperation(img, gradientImg, CV_MOP_GRADIENT);
	SnapShow(gradientImg, "Gradient Image");
}

void DoTopHatMorphologyOperation(const cv::Mat& img)
{
	cv::Mat tophatImg;
	MorphologyOperation(img, tophatImg, CV_MOP_TOPHAT);
	SnapShow(tophatImg, "Top-Hat Image");
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

	DoOpenMorphologyOperation(img);

	DoGradientMorphologyOperation(img);

	DoTopHatMorphologyOperation(img);

	system("Pause");
	return 0;
}
