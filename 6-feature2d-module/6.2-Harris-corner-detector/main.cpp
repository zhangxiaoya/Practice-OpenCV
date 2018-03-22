#include <iostream>
#include <core/core.hpp>
#include <highgui.h>
#include <contrib/contrib.hpp>

cv::Mat srcImg;
cv::Mat grayImg;

int thresh = 200;
int maxThresh = 255;

char* sourceWindows = "Source Windows";
char* cornerWindows = "Corner Windows";

void cornerHarrisDemo(int, void*)
{
	cv::Mat dstNorm;
	cv::Mat dstNormScaled;
	cv::Mat dstImg = cv::Mat::zeros(srcImg.size(), CV_32FC1);

	auto blockSize = 2;
	auto apertureSize = 3;
	auto K = 0.04;

	cornerHarris(grayImg, dstImg, blockSize, apertureSize, K);

	normalize(dstImg, dstNorm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
	convertScaleAbs(dstNorm, dstNormScaled);

	for (auto j = 0; j < dstNorm.rows; ++j)
	{
		for (auto i = 0; i < dstNorm.cols; ++i)
		{
			if (static_cast<int>(dstNorm.at<float>(j, i)) > thresh)
			{
				circle(dstNormScaled, cv::Point(i, j), 5, cv::Scalar(0));
			}
		}
	}
	cv::namedWindow(cornerWindows);
	imshow(cornerWindows, dstNormScaled);
}

int main(int argc, char* argv[])
{
	srcImg = cv::imread("D:\\Bags\\Github\\opencv\\samples\\c\\one_way_train_0000.jpg", 1);
	cvtColor(srcImg, grayImg, CV_RGB2GRAY);
	cv::namedWindow(sourceWindows);
	cv::createTrackbar("Threshold:", sourceWindows, &thresh, maxThresh, cornerHarrisDemo);
	imshow(sourceWindows, srcImg);

	cornerHarrisDemo(0, nullptr);
	cv::waitKey(0);

	return 0;
}
