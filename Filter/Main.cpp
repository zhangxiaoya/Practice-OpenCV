#include <iostream>
#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include <contrib/contrib.hpp>

#include "Utils/PerformanceUtil.hpp"
void SculptureFilter(const cv::Mat sourceImage, cv::Mat resultImage, int flag = 0)
{
	auto res = 0;

	for (auto i = 1; i < sourceImage.rows - 1; ++i)
	{
		auto preRow = sourceImage.ptr<uchar>(i - 1);
		auto nextRow = sourceImage.ptr<uchar>(i + 1);

		auto curRow = resultImage.ptr<uchar>(i);

		for (auto j = 1; j < sourceImage.cols - 1; ++j)
		{
			auto channel = 3;
			while (channel > 0)
			{
				channel--;

				if (flag == 0)
					res = nextRow[3 * (j + 1) + channel] - preRow[3 * (j - 1) + channel] + 128;
				else if (flag == 1)
					res = preRow[3 * (j + 1) + channel] - nextRow[3 * (j - 1) + channel] + 128;

				if (res > 255)
					res = 255;
				else if (res < 0)
					res = 0;
				curRow[3 * j + channel] = res;
			}
		}
	}
}

void ZoomFilter(const cv::Mat sourceImage, cv::Mat resultImage, int flag = 0)
{
	cv::Point center(sourceImage.cols / 2, sourceImage.rows / 2);
	sourceImage.copyTo(resultImage);

	int R = sqrt(sourceImage.cols * sourceImage.cols + sourceImage.rows * sourceImage.rows) / 2;
	for (auto i = 0; i < resultImage.rows; ++i)
	{
		auto curRow = resultImage.ptr<uchar>(i);
		for (auto j = 0; j < resultImage.cols; ++j)
		{
			int dis = cv::norm(cv::Point(j, i) - center);
			if (dis < R)
			{
				auto newI = (i - center.y) * dis / R + center.y;
				auto newJ = (j - center.x) * dis / R + center.x;

				curRow[3 * j + 0] = sourceImage.at<uchar>(newI, newJ * 3 + 0);
				curRow[3 * j + 1] = sourceImage.at<uchar>(newI, newJ * 3 + 1);
				curRow[3 * j + 2] = sourceImage.at<uchar>(newI, newJ * 3 + 2);
			}
		}
	}
}

void ColorMapFilter(const cv::Mat& sourceImage, const cv::Mat& resultImage)
{
	auto width = sourceImage.cols;
	auto height = sourceImage.rows;

	cv::Mat gray;
	cv::Mat imageColors[12];

	cvtColor(sourceImage, gray, CV_BGR2GRAY);
	for (auto i = 0; i < 12; ++i)
	{
		applyColorMap(gray, imageColors[i], i);
		auto row = i / 4;
		auto col = i % 4;
		auto currntROI = resultImage(cv::Rect(col * width, row * height, width, height));
		resize(imageColors[i], currntROI, currntROI.size());
	}
}

void SketchFilter(const cv::Mat& sourceImage, cv::Mat& resultImage)
{
	cv::Mat grayImg;
	cv::Mat inverseColorImg;

	cvtColor(sourceImage, grayImg, CV_BGR2GRAY);

	addWeighted(grayImg, -1, NULL, 0, 255, inverseColorImg);

	GaussianBlur(inverseColorImg, inverseColorImg, cv::Size(11, 11), 0);

	for (auto i = 0; i < grayImg.rows; ++i)
	{
		auto pGray = grayImg.ptr<uchar>(i);
		auto pInverse = inverseColorImg.ptr<uchar>(i);
		auto pCurrent = resultImage.ptr<uchar>(i);

		for (auto j = 0; j < grayImg.cols; ++j)
		{
			pCurrent[j] = static_cast<uchar>(min((pGray[j]) + (pGray[j] * pInverse[j]) / (255 - pInverse[j]), 255));
		}
	}
}

void FrostedGlassFilter(const cv::Mat& sourceImage, cv::Mat& resultImage)
{
	cv::RNG rng;
	for (auto i = 1; i < sourceImage.rows - 1; ++i)
	{
		const auto pCur = resultImage.ptr<uchar>(i);

		for (auto j = 1; j < sourceImage.cols - 1; ++j)
		{
			auto redomIndex = rng.uniform(0, 9);
			auto srcRow = (i - 1) + redomIndex / 3;
			auto srcCol = (j - 1) + redomIndex % 3;
			pCur[3 * j + 0] = sourceImage.at<uchar>(srcRow, srcCol * 3 + 0);
			pCur[3 * j + 1] = sourceImage.at<uchar>(srcRow, srcCol * 3 + 1);
			pCur[3 * j + 2] = sourceImage.at<uchar>(srcRow, srcCol * 3 + 2);
		}
	}
}

void NagetiveFilter(const cv::Mat& sourceImage, cv::Mat& resultImage)
{
	for (auto i = 0; i < sourceImage.rows; ++i)
	{
		auto pSrc = sourceImage.ptr<uchar>(i);
		auto pCur = resultImage.ptr<uchar>(i);

		for (auto j = 0; j < sourceImage.cols; ++j)
		{
			pCur[j * 3 + 0] = 255 - pSrc[j * 3 + 0];
			pCur[j * 3 + 1] = 255 - pSrc[j * 3 + 1];
			pCur[j * 3 + 2] = 255 - pSrc[j * 3 + 2];
		}
	}
}

void SnapShow(const cv::Mat& img, const char* winname)
{
	cv::namedWindow(winname);
	imshow(winname, img);
	cv::waitKey(0);
	cv::destroyWindow(winname);
}

int main()
{
	auto sourceImage = cv::imread(".\\lena.png");
	if (sourceImage.empty())
	{
		std::cout << "Read Image File Failed!" << std::endl;
		system("Pause");
		return -1;
	}
	
	SnapShow(sourceImage, "Source Image");

	cv::Mat sculptureResultImageWithThreeDegree(sourceImage.size(), CV_8UC3);
	SculptureFilter(sourceImage, sculptureResultImageWithThreeDegree);

	SnapShow(sculptureResultImageWithThreeDegree, "Filter Image");

	cv::Mat sculptureResultImageWithThreeDegreeMore(sourceImage.size(), CV_8UC3);
	SculptureFilter(sourceImage, sculptureResultImageWithThreeDegreeMore, 1);

	SnapShow(sculptureResultImageWithThreeDegreeMore, "Filter Image More");

	cv::Mat zoomResultImage(sourceImage.size(), CV_8UC3);
	ZoomFilter(sourceImage, zoomResultImage);

	SnapShow(zoomResultImage, "Zoom Filter Image");

	cv::Mat colorMapResultImage(sourceImage.rows * 3, sourceImage.cols * 4, CV_8UC3);
	ColorMapFilter(sourceImage, colorMapResultImage);

	SnapShow(colorMapResultImage, "Zoom Filter Image");

	cv::Mat sketckResultImage(sourceImage.size(), CV_8U);
	SketchFilter(sourceImage, sketckResultImage);

	SnapShow(sketckResultImage, "Sketck Image");

	cv::Mat frostedGlassResultImage(sourceImage.size(), CV_8UC3);
	FrostedGlassFilter(sourceImage, frostedGlassResultImage);

	SnapShow(frostedGlassResultImage, "Frosted Glass Filter Image");

	cv::Mat negativeResultImage(sourceImage.size(), CV_8UC3);
	NagetiveFilter(sourceImage, negativeResultImage);

	SnapShow(negativeResultImage, "Frosted Glass Filter Image");

	system("Pause");
	return 0;
}
