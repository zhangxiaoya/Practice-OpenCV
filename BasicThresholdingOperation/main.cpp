#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

auto const MaxBinaryValue = 255;
auto const MaxValue = 255;
auto const MaxType = 4;

const char* const WindowName = "Threshold Demo";

const char* const trackbarType = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* const trackbarValue = "Value";

struct Data
{
	int thresholdType;
	int thresholdValue;
	cv::Mat sourceImg;

	Data() : thresholdType(3), thresholdValue(0)
	{
	}
};

void UpdateView(Data* const dataPtr)
{
	/* 0: Binary
	1: Binary Inverted
	2: Threshold Truncated
	3: Threshold to Zero
	4: Threshold to Zero Inverted
	*/
	cv::Mat dst;

	threshold(dataPtr->sourceImg, dst, dataPtr->thresholdValue, MaxBinaryValue, dataPtr->thresholdType);
	imshow(WindowName, dst);
}

void UpdateThresholdType(int thresholdType, void* data)
{
	UpdateView(static_cast<Data*>(data));
}

void UpdateThresholdValue(int thresholdValue, void* data)
{
	UpdateView(static_cast<Data*>(data));
}

int main(int argc, char* argv[])
{
	auto src = cv::imread("..\\data\\lena.png", 1);
	if (src.empty())
	{
		std::cout << "Read Image File Failed!" << std::endl;
		system("Pause");
		return -1;
	}
	
	cv::Mat srcGray;
	cvtColor(src, srcGray, CV_RGB2GRAY);

	Data transferData;
	transferData.sourceImg = srcGray;

	cv::namedWindow(WindowName, CV_WINDOW_AUTOSIZE);

	UpdateView(&transferData);

	cv::createTrackbar(trackbarType, WindowName, &transferData.thresholdType, MaxType, UpdateThresholdType, static_cast<void*>(&transferData));

	cv::createTrackbar(trackbarValue, WindowName, &transferData.thresholdValue, MaxValue, UpdateThresholdValue, static_cast<void*>(&transferData));

	cv::waitKey(0);

	cv::destroyWindow(WindowName);
	return 0;
}
