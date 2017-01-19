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
	return 0;
}
