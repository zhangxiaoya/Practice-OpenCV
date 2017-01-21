#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "Can not open camera" << endl;
		return -1;
	}
	Mat frame;
	Mat edges;
	bool isBreakByUser = false;
	while (!isBreakByUser)
	{
		cap >> frame;
		imshow("Current Video", frame);
		if (waitKey(30) >= 0)
			isBreakByUser = true;
	}
	return 0;
}
