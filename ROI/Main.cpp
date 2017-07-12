#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
	auto img = cv::imread(".\\lena.png");
	cv::Rect rect(180, 200, 200, 200);
	auto roi = cv::Mat(img, rect);
	auto imgClone = img.clone();
	rectangle(imgClone, rect, cv::Scalar(0, 255, 0), 2);
	imshow("Original image with rectangle", imgClone);
	imshow("ROI", roi);
	cv::waitKey(0);

	// first method
	auto grayImg = cv::Mat(300, 400, CV_8U);
	for (auto i = 0; i < grayImg.rows; ++i)
	{
		for (auto j = 0; j < grayImg.cols; ++j)
		{
			grayImg.at<uchar>(i, j) = (i + j) % 255;
		}
	}
	imshow("grayImg", grayImg);
	cv::waitKey(0);

	auto rgbImg = cv::Mat(300, 400, CV_8UC3);
	for (auto i = 0; i < rgbImg.rows; ++i)
	{
		for (auto j = 0; j < rgbImg.cols; ++j)
		{
			rgbImg.at<cv::Vec3b>(i, j)[0] = i % 255;
			rgbImg.at<cv::Vec3b>(i, j)[1] = j % 255;
			rgbImg.at<cv::Vec3b>(i, j)[2] = 0;
		}
	}
	imshow("RGB image", rgbImg);
	cv::waitKey(0);

	// second method
	auto grayImg2 = cv::Mat(300, 400, CV_8U);
	cv::MatIterator_<uchar> grayIt, grayEnd;
	for (grayIt = grayImg2.begin<uchar>() , grayEnd = grayImg2.end<uchar>(); grayIt != grayEnd; ++grayIt)
	{
		*grayIt = rand() % 255;
	}
	imshow("Gray Image 2", grayImg2);
	cv::waitKey();
	auto rgbImge2 = cv::Mat(300, 400, CV_8UC3);
	cv::MatIterator_<cv::Vec3b> rgbIt, rgbEnd;
	for (rgbIt = rgbImge2.begin<cv::Vec3b>() , rgbEnd = rgbImge2.end<cv::Vec3b>(); rgbIt != rgbEnd; ++rgbIt)
	{
		(*rgbIt)[0] = rand() % 255;
		(*rgbIt)[1] = rand() % 255;
		(*rgbIt)[2] = rand() % 255;
	}
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
