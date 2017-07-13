#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>

const auto CameraId = 0;

int main()
{
	cv::VideoCapture capture(CameraId);
	if (!capture.isOpened())
	{
		std::cout << "Can Not Open Camera " << std::setw(2) << CameraId << std::endl;
		system("Pause");
		return -1;
	}

	cv::Mat frame;
	auto isBreakByUser = false;
	while (!isBreakByUser)
	{
		capture >> frame;
		imshow("Current Video", frame);
		if (cv::waitKey(30) >= 0)
			isBreakByUser = true;
	}

	system("Pause");
	return 0;
}
