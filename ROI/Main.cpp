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


	// first method
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

	// second method
	Mat grayImg2 = Mat(300, 400, CV_8U);
	MatIterator_<uchar> grayIt, grayEnd;
	for (grayIt = grayImg2.begin<uchar>(), grayEnd = grayImg2.end<uchar>(); grayIt != grayEnd; ++grayIt)
	{
		*grayIt = rand() % 255;
	}
	imshow("Gray Image 2",grayImg2);
	waitKey();
	Mat rgbImge2 = Mat(300, 400, CV_8UC3);
	MatIterator_<Vec3b> rgbIt, rgbEnd;
	for (rgbIt = rgbImge2.begin<Vec3b>(), rgbEnd = rgbImge2.end<Vec3b>(); rgbIt != rgbEnd;++rgbIt)
	{
		(*rgbIt)[0] = rand() % 255;
		(*rgbIt)[1] = rand() % 255;
		(*rgbIt)[2] = rand() % 255;
	}
	imshow("RGB Image 2", rgbImge2);
	waitKey();

	// third method
	Mat grayImg3 = Mat(300, 400, CV_8U);
	for (int i = 0; i < grayImg3.rows;++i)
	{
		uchar* p = grayImg3.ptr < uchar>(i);
		for (int j = 0; j < grayImg3.cols;++j)
		{
			p[j] = (i + j) % 255;
		}
	}
	imshow("Gray Image 3", grayImg3);
	waitKey();
	Mat rgbImg3 = Mat(300, 400, CV_8UC3);
	for (int i = 0; i < rgbImg3.rows;++i)
	{
		Vec3b* p = rgbImg3.ptr<Vec3b>(i);
		for (int j = 0; j < rgbImg3.cols;++j)
		{
			p[j][0] = (i + j) % 255;
			p[j][1] = (i + j) % 255;
			p[j][2] = 0;
		}
	}
	imshow("RGB Image 3", rgbImg3);
	waitKey();

	// use step
	Mat grayImg4 = Mat(300, 400, CV_8U, Scalar(0));
	for (int i = 0; i < grayImg4.rows;++i)
	{
		for (int j = 0; j < grayImg4.cols;++j)
		{
			cout << (int)(*(grayImg4.data + grayImg4.step[0] * i + grayImg4.step[1] * j)) <<" ==> "<<endl;
			*(grayImg4.data + grayImg4.step[0] * i + grayImg4.step[1] * j) = 255;
			cout << (int)(*(grayImg4.data + grayImg4.step[0] * i + grayImg4.step[1] * j)) << endl;
		}
	}
	imshow("Gray Image 4", grayImg4);
	waitKey();
	return 0;
}
