#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

void SculptureFilter(const cv::Mat sourceImage, cv::Mat resultImage, int flag = 0)
{
	int res = 0;

	for (int i = 1; i < sourceImage.rows - 1; ++i)
	{
		const uchar* preRow = sourceImage.ptr<uchar>(i - 1);
		const uchar* nextRow = sourceImage.ptr<uchar>(i + 1);

		uchar* curRow = resultImage.ptr<uchar>(i);

		for (int j = 1; j < sourceImage.cols - 1; ++j)
		{
			int channel = 3;
			while (channel > 0)
			{
				channel--;
				
				if(flag ==0)
					res = nextRow[3 * (j + 1) + channel] - preRow[3 * (j - 1) + channel] + 128;
				else if(flag == 1)
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

	int R = sqrt(sourceImage.cols* sourceImage.cols + sourceImage.rows * sourceImage.rows) / 2;
	for (int i = 0; i < resultImage.rows;++i)
	{
		uchar* curRow = resultImage.ptr<uchar>(i);
		for (int j = 0; j < resultImage.cols;++j)
		{
			int dis = cv::norm(cv::Point(j, i) - center);
			if(dis < R)
			{
				int newI = (i - center.y) * dis / R + center.y;
				int newJ = (j - center.x) * dis / R + center.x;

				curRow[3 * j + 0] = sourceImage.at<uchar>(newI, newJ * 3 + 0);
				curRow[3 * j + 1] = sourceImage.at<uchar>(newI, newJ * 3 + 1);
				curRow[3 * j + 2] = sourceImage.at<uchar>(newI, newJ * 3 + 2);
			}
		}
	}
}

void ColorMapFilter(const cv::Mat& sourceImage, const cv::Mat& resultImage)
{
	int width = sourceImage.cols;
	int height = sourceImage.rows;

	cv::Mat gray;
	cv::Mat imageColors[12];

	cv::cvtColor(sourceImage,gray, CV_BGR2GRAY);
	for (int i = 0; i < 12;++i)
	{
		cv::applyColorMap(gray, imageColors[i], i);
		int row = i / 4;
		int col = i % 4;
		cv::Mat currntROI = resultImage(cv::Rect(col * width, row*height, width, height));
		cv::resize(imageColors[i], currntROI, currntROI.size());
	}
}

void SketchFilter(const cv::Mat& sourceImage, cv::Mat& resultImage)
{
	cv::Mat grayImg;
	cv::Mat inverseColorImg;

	cvtColor(sourceImage, grayImg, CV_BGR2GRAY);

	cv::addWeighted(grayImg, -1, NULL, 0, 255, inverseColorImg);
	
	cv::GaussianBlur(inverseColorImg, inverseColorImg, cv::Size(11, 11), 0);

	for (int i = 0; i < grayImg.rows;++i)
	{
		uchar* pGray = grayImg.ptr<uchar>(i);
		uchar* pInverse = inverseColorImg.ptr<uchar>(i);
		uchar* pCurrent = resultImage.ptr<uchar>(i);

		for (int j = 0; j < grayImg.cols;++j)
		{
			pCurrent[j] = static_cast<uchar>(cv::min((pGray[j]) + (pGray[j] * pInverse[j]) / (255 - pInverse[j]), 255));
		}
	}
}

void FrostedGlassFilter(const cv::Mat& sourceImage,  cv::Mat& resultImage)
{
	cv::RNG rng;
	for (int i = 1; i < sourceImage.rows-1;++i)
	{
		uchar* const pCur = resultImage.ptr<uchar>(i);

		for (int j = 1; j < sourceImage.cols-1;++j)
		{
			int redomIndex = rng.uniform(0, 9);
			int srcRow = (i - 1) + redomIndex / 3;
			int srcCol = (j - 1) + redomIndex % 3;
			pCur[3 * j + 0] = sourceImage.at<uchar>(srcRow, srcCol * 3 + 0);
			pCur[3 * j + 1] = sourceImage.at<uchar>(srcRow, srcCol * 3 + 1);
			pCur[3 * j + 2] = sourceImage.at<uchar>(srcRow, srcCol * 3 + 2);
		}
	}
}

int main()
{
	cv::Mat sourceImage = cv::imread("lena.png");
	if(sourceImage.empty())
	{
		cout << "Error: can not read file!";
	}
	imshow("Source Image", sourceImage);

	cv::Mat sculptureResultImageWithThreeDegree(sourceImage.size(), CV_8UC3);
	cv::Mat sculptureResultImageWithThreeDegreeMore(sourceImage.size(), CV_8UC3);

	SculptureFilter(sourceImage, sculptureResultImageWithThreeDegree);
	SculptureFilter(sourceImage, sculptureResultImageWithThreeDegreeMore,1);

	imshow("Filter Image", sculptureResultImageWithThreeDegree);
	imshow("Filter Image More", sculptureResultImageWithThreeDegreeMore);

	cv::Mat zoomResultImage(sourceImage.size(), CV_8UC3);

	ZoomFilter(sourceImage, zoomResultImage);

	imshow("Zoom Filter Image", zoomResultImage);

	cv::Mat colorMapResultImage(sourceImage.rows * 3, sourceImage.cols*4, CV_8UC3);

	ColorMapFilter(sourceImage, colorMapResultImage);

	imshow("Zoom Filter Image", colorMapResultImage);

	cv::Mat sketckResultImage(sourceImage.size(), CV_8U);

	SketchFilter(sourceImage,sketckResultImage);

	cv::imshow("Sketck Image", sketckResultImage);

	cv::Mat frostedGlassResultImage(sourceImage.size(), CV_8UC3);

	FrostedGlassFilter(sourceImage, frostedGlassResultImage);

	cv::imshow("Frosted Glass Filter Image", frostedGlassResultImage);
	cv::waitKey();
	return 0;
}
