#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

auto thresholdValue = 0;
auto thresholdType = 3;
auto const maxValue = 255;
auto const maxType = 4;
auto const maxBinaryValue = 255;

cv::Mat srcGray;
cv::Mat dst;
char* WindowName = "Threshold Demo";

char* trackbarType = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
char* trackbarValue = "Value";

void ThresholdDemo(int, void*)
{
	/* 0: Binary
	1: Binary Inverted
	2: Threshold Truncated
	3: Threshold to Zero
	4: Threshold to Zero Inverted
	*/
	threshold(srcGray, dst, thresholdValue, maxBinaryValue, thresholdType);
	imshow(WindowName, dst);
}

int main(int argc, char* argv[])
{
	auto src = cv::imread("lena.png", 1);
	if (src.empty())
	{
		std::cout << "Read Image File Failed!" << std::endl;
		system("Pause");
		return -1;
	}
	cvtColor(src, srcGray, CV_RGB2GRAY);

	cv::namedWindow(WindowName, CV_WINDOW_AUTOSIZE);

	cv::createTrackbar(trackbarType, WindowName, &thresholdType, maxType, ThresholdDemo);

	cv::createTrackbar(trackbarValue, WindowName, &thresholdValue, maxValue, ThresholdDemo);

	ThresholdDemo(0, nullptr);

	cv::waitKey(0);

	return 0;
}
