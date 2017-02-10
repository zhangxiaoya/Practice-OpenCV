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
int main()
{
	cv::Mat sourceImage = cv::imread("lena.png");
	if(sourceImage.empty())
	{
		cout << "Error: can not read file!";
	}
	cv::imshow("Source Image", sourceImage);

	cv::Mat sculptureResultImageWithThreeDegree(sourceImage.size(), CV_8UC3);
	cv::Mat sculptureResultImageWithThreeDegreeMore(sourceImage.size(), CV_8UC3);

	SculptureFilter(sourceImage, sculptureResultImageWithThreeDegree);
	SculptureFilter(sourceImage, sculptureResultImageWithThreeDegreeMore,1);

	cv::imshow("Filter Image", sculptureResultImageWithThreeDegree);
	cv::imshow("Filter Image More", sculptureResultImageWithThreeDegreeMore);

	cv::waitKey();
	return 0;
}