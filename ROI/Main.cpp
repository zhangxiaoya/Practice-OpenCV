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
			grayImg.at<uchar>(i, j) = rand() % 255;
		}
	}
}

void GenerateRGBImageUseAtOperator(cv::Mat& rgbImg)
{
	for (auto i = 0; i < rgbImg.rows; ++i)
	{
		for (auto j = 0; j < rgbImg.cols; ++j)
		{
			rgbImg.at<cv::Vec3b>(i, j)[0] = rand() % 255;;
			rgbImg.at<cv::Vec3b>(i, j)[1] = rand() % 255;;
			rgbImg.at<cv::Vec3b>(i, j)[2] = rand() % 255;;
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

int main()
{
	auto img = cv::imread(".\\lena.png");
	if (img.empty())
	{
		std::cout << "Read image file failed!" << std::endl;
		system("Pause");
		return -1;
	}

	imshow("Original image with rectangle", img);
	cv::waitKey(0);

	cv::Rect rect(180, 200, 200, 200);

	auto imgClone = img.clone();
	rectangle(imgClone, rect, cv::Scalar(0, 255, 0), 2);
	imshow("Original image with rectangle", imgClone);
	cv::waitKey(0);

	auto roi = cv::Mat(img, rect);
	imshow("ROI", roi);
	cv::waitKey(0);

	// visit image the first methd -- use at operator
	auto grayImg = cv::Mat(300, 400, CV_8U);
	CheckPerf(GenerateGrayImageUseAtOperator(grayImg), "GenerateGrayImageUseAtOperator");
	imshow("grayImg", grayImg);
	cv::waitKey(0);

	auto rgbImg = cv::Mat(300, 400, CV_8UC3);
	CheckPerf(GenerateRGBImageUseAtOperator(rgbImg), "GenerateRGBImageUseAtOperator");
	imshow("RGB image", rgbImg);
	cv::waitKey(0);

	// visit iamge the second method -- use mat iterator
	auto grayImg2 = cv::Mat(300, 400, CV_8U);
	CheckPerf(GenerateGrayImageUseMatIterator(grayImg2), "GenerateGrayImageUseMatIterator");
	imshow("Gray Image 2", grayImg2);
	cv::waitKey(0);

	auto rgbImge2 = cv::Mat(300, 400, CV_8UC3);
	CheckPerf(GenerateRGBImageUseMatIterator(rgbImge2), "GenerateRGBImageUseMatIterator");
	imshow("RGB Image 2", rgbImge2);
	cv::waitKey();

	// third method
	auto grayImg3 = cv::Mat(300, 400, CV_8U);
	for (auto i = 0; i < grayImg3.rows; ++i)
	{
		auto p = grayImg3.ptr<uchar>(i);
		for (auto j = 0; j < grayImg3.cols; ++j)
		{
			p[j] = (i + j) % 255;
		}
	}
	imshow("Gray Image 3", grayImg3);
	cv::waitKey();
	auto rgbImg3 = cv::Mat(300, 400, CV_8UC3);
	for (auto i = 0; i < rgbImg3.rows; ++i)
	{
		auto p = rgbImg3.ptr<cv::Vec3b>(i);
		for (auto j = 0; j < rgbImg3.cols; ++j)
		{
			p[j][0] = (i + j) % 255;
			p[j][1] = (i + j) % 255;
			p[j][2] = 0;
		}
	}
	imshow("RGB Image 3", rgbImg3);
	cv::waitKey();

	// use step
	auto grayImg4 = cv::Mat(300, 400, CV_8U, cv::Scalar(0));
	for (auto i = 0; i < grayImg4.rows; ++i)
	{
		for (auto j = 0; j < grayImg4.cols; ++j)
		{
			std::cout << static_cast<int>(*(grayImg4.data + grayImg4.step[0] * i + grayImg4.step[1] * j)) << " ==> " << std::endl;
			*(grayImg4.data + grayImg4.step[0] * i + grayImg4.step[1] * j) = 255;
			std::cout << static_cast<int>(*(grayImg4.data + grayImg4.step[0] * i + grayImg4.step[1] * j)) << std::endl;
		}
	}
	imshow("Gray Image 4", grayImg4);
	cv::waitKey();
	return 0;
}
