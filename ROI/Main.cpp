#pragma once

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Utils/PerformanceUtil.hpp"

void GenerateGrayImageUseAtOperator(cv::Mat& grayImg)
{
	for (auto i = 0; i < grayImg.rows; ++i)
	{
		for (auto j = 0; j < grayImg.cols; ++j)
		{
			grayImg.at<uchar>(i, j) = (i + j) % 255;
		}
	}
}

void GenerateRGBImageUseAtOperator(cv::Mat& rgbImg)
{
	for (auto i = 0; i < rgbImg.rows; ++i)
	{
		for (auto j = 0; j < rgbImg.cols; ++j)
		{
			rgbImg.at<cv::Vec3b>(i, j)[0] = i % 255;;
			rgbImg.at<cv::Vec3b>(i, j)[1] = j % 255;;
			rgbImg.at<cv::Vec3b>(i, j)[2] = (i + j) % 255;;
		}
	}
}

void GenerateGrayImageUseMatIterator(cv::Mat& grayImg)
{
	cv::MatIterator_<uchar> grayIt, grayEnd;
	for (grayIt = grayImg.begin<uchar>() , grayEnd = grayImg.end<uchar>(); grayIt != grayEnd; ++grayIt)
	{
		*grayIt = rand() % 255;
	}
}

void GenerateRGBImageUseMatIterator(cv::Mat& rgbImge)
{
	cv::MatIterator_<cv::Vec3b> rgbIt, rgbEnd;
	for (rgbIt = rgbImge.begin<cv::Vec3b>() , rgbEnd = rgbImge.end<cv::Vec3b>(); rgbIt != rgbEnd; ++rgbIt)
	{
		(*rgbIt)[0] = rand() % 255;
		(*rgbIt)[1] = rand() % 255;
		(*rgbIt)[2] = rand() % 255;
	}
}

void GenerateGrayImageUsePtr(cv::Mat& grayImg)
{
	for (auto i = 0; i < grayImg.rows; ++i)
	{
		auto p = grayImg.ptr<uchar>(i);
		for (auto j = 0; j < grayImg.cols; ++j)
		{
			p[j] = (i + j) % 255;
		}
	}
}

void GenerateRGBImageUsePtr(cv::Mat& rgbImg)
{
	for (auto i = 0; i < rgbImg.rows; ++i)
	{
		auto p = rgbImg.ptr<cv::Vec3b>(i);
		for (auto j = 0; j < rgbImg.cols; ++j)
		{
			p[j][0] = (i + j) % 255;
			p[j][1] = (i + j) % 255;
			p[j][2] = 0;
		}
	}
}

void GenerateGrayImageUseStep(cv::Mat& grayImg)
{
	for (auto i = 0; i < grayImg.rows; ++i)
	{
		for (auto j = 0; j < grayImg.cols; ++j)
		{
			*(grayImg.data + grayImg.step[0] * i + grayImg.step[1] * j) = (i + j) % 255;
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
	auto img = cv::imread(".\\lena.png");
	if (img.empty())
	{
		std::cout << "Read image file failed!" << std::endl;
		system("Pause");
		return -1;
	}

	SnapShow(img, "Original image");

	cv::Rect rect(180, 200, 200, 200);

	auto imgClone = img.clone();
	rectangle(imgClone, rect, cv::Scalar(0, 255, 0), 2);

	SnapShow(imgClone, "Original image with rectangle");

	auto roi = cv::Mat(img, rect);

	SnapShow(roi, "ROI");

	auto height = img.rows;
	auto width = img.cols;

	// visit image the first methd -- use at operator
	auto grayImg = cv::Mat(height, width, CV_8U);
	CheckPerf(GenerateGrayImageUseAtOperator(grayImg), "GenerateGrayImageUseAtOperator");

	SnapShow(grayImg, "grayImg");

	auto rgbImg = cv::Mat(height, width, CV_8UC3);
	CheckPerf(GenerateRGBImageUseAtOperator(rgbImg), "GenerateRGBImageUseAtOperator");

	SnapShow(rgbImg, "RGB image");

	// visit iamge the second method -- use mat iterator
	auto grayImg2 = cv::Mat(height, width, CV_8U);
	CheckPerf(GenerateGrayImageUseMatIterator(grayImg2), "GenerateGrayImageUseMatIterator");

	SnapShow(grayImg2, "Gray Image 2");

	auto rgbImge2 = cv::Mat(height, width, CV_8UC3);
	CheckPerf(GenerateRGBImageUseMatIterator(rgbImge2), "GenerateRGBImageUseMatIterator");

	SnapShow(rgbImge2, "RGB Image 2");

	// visit iamge the third method -- use ptr point
	auto grayImg3 = cv::Mat(height, width, CV_8U);
	CheckPerf(GenerateGrayImageUsePtr(grayImg3), "GenerateGrayImageUsePtr");

	SnapShow(grayImg3, "Gray Image 3");

	auto rgbImg3 = cv::Mat(height, width, CV_8UC3);
	CheckPerf(GenerateRGBImageUsePtr(rgbImg3), "GenerateRGBImageUsePtr");

	SnapShow(rgbImg3, "RGB Image 3");

	// visit image the forth method -- use step
	auto grayImg4 = cv::Mat(height, width, CV_8U, cv::Scalar(0));
	CheckPerf(GenerateGrayImageUseStep(grayImg4), "GenerateGrayImageUseStep");
	SnapShow(grayImg4, "Gray Image 4");

	return 0;
}
