#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main()
{
	cv::Mat sourceImage = cv::imread("lena.png");
	if(sourceImage.empty())
	{
		cout << "Error: can not read file!";
	}
	cv::Mat sculptureResultImageWithThreeDegree(sourceImage.size(), CV_8UC3);
	cv::Mat sculptureResultImageWithThreeDegreeMore(sourceImage.size(), CV_8UC3);

	cv::imshow("Source Image", sourceImage);

	for (int i = 1; i < sourceImage.rows - 1;++i)
	{
		uchar* preRow = sourceImage.ptr<uchar>(i-1);
		uchar* nextRow = sourceImage.ptr<uchar>(i+1);

		uchar* curRow = sculptureResultImageWithThreeDegree.ptr<uchar>(i);
		uchar* curRowMore = sculptureResultImageWithThreeDegreeMore.ptr<uchar>(i);

		for (int j = 1; j < sourceImage.cols - 1;++j)
		{
			int channel = 3;
			while(channel > 0)
			{
				channel--;
				int res = nextRow[3 * (j + 1) + channel] - preRow[3 * (j - 1) + channel] + 128;

				if (res > 255)
					res = 255;
				else if (res < 0)
					res = 0;
				curRow[3 * j + channel] = res;

				int resMore = preRow[3 * (j + 1) + channel] - nextRow[3 * (j - 1) + channel] + 128;
				if (resMore > 255)
					resMore = 255;
				else if (resMore < 0)
					resMore = 0;
				curRowMore[3 * j + channel] = resMore;
			}
		}
	}

	cv::imshow("Filter Image", sculptureResultImageWithThreeDegree);
	cv::imshow("Filter Image More", sculptureResultImageWithThreeDegreeMore);
	cv::waitKey();
	return 0;
}