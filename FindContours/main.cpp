#include "cv.h"
#include "highgui.h"

using namespace cv;

int main(int argc, char** argv)
{
	char fullName[100];
	std::string forMat = "E:\\WorkLogs\\Frame_%02d.png";
	auto count = 18;

	for (auto i = 0; i < count; ++i)
	{
		sprintf_s(fullName, 100, forMat.c_str(),i);
		auto src = imread(fullName, 0);

		Mat dst = Mat::zeros(src.rows, src.cols, CV_8UC3);

		namedWindow("Source", 1);
		imshow("Source", src);

		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;

		findContours(src, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

		if(contours.size() == 0)
			continue;

		for (auto idx = 0; idx >= 0; idx = hierarchy[idx][0])
		{
			Scalar color(rand() & 255, rand() & 255, rand() & 255);
			drawContours(dst, contours, idx, color, CV_FILLED, 8, hierarchy);
		}

		namedWindow("Components", 1);
		imshow("Components", dst);
		waitKey(1000);
	}

	destroyAllWindows();
	return 0;
}