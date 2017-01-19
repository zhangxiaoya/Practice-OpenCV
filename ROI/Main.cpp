#include "Main.h"
#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("lena.png");
	Rect rect(180, 200, 200, 200);
	Mat roi = Mat(img, rect);
	Mat imgClone = img.clone();
	rectangle(imgClone, rect, Scalar(0, 255, 0), 2);
	imshow("Original image with rectangle", imgClone);
	imshow("ROI", roi);
	waitKey(0);

	Mat grayImg = Mat(300, 400, CV_8U);
	for (int i = 0; i < grayImg.rows;++i)
	{
		for (int j = 0; j < grayImg.cols;++j)
		{
			grayImg.at<uchar>(i, j) = (i + j) % 255;
		}
	}
	imshow("grayImg", grayImg);
	waitKey(0);
	Mat rgbImg = Mat(300, 400, CV_8UC3);
	for (int i = 0; i < rgbImg.rows;++i)
	{
		for (int j = 0; j < rgbImg.cols;++j)
		{
			rgbImg.at<Vec3b>(i, j)[0] = i % 255;
			rgbImg.at<Vec3b>(i, j)[1] = j % 255;
			rgbImg.at<Vec3b>(i, j)[2] = 0;
		}
	}
	imshow("RGB image", rgbImg);
	waitKey(0);
	return 0;
}
