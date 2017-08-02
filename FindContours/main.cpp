#include "cv.h"
#include "highgui.h"

using namespace cv;

int main(int argc, char** argv)
{
	char fullName[100];
	string forMat = "..\\data\\Maks\\Mask_%02d.png";
	auto count = 18;
	RNG rng(12345);

	for (auto i = 0; i < count; ++i)
	{
		sprintf_s(fullName, 100, forMat.c_str(), i);
		auto src = imread(fullName, 0);

		if (src.empty() == true)
		{
			std::cout << "Read Image File Failed" << std::endl;
			system("Pause");
			return -1;
		}

		Mat dst = Mat::zeros(src.rows, src.cols, CV_8UC3);

		namedWindow("Source", 1);
		imshow("Source", src);

		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		findContours(src, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

		if (contours.size() == 0)
			continue;

		for (auto idx = 0; idx >= 0; idx = hierarchy[idx][0])
		{
			Scalar color(rand() & 255, rand() & 255, rand() & 255);
			drawContours(dst, contours, idx, color, CV_FILLED, 8, hierarchy);
		}
		imshow("Draw Contours", dst);

		vector<vector<Point>> contours_poly(contours.size());
		vector<Rect> boundRect(contours.size());

		for (auto j = 0; j < contours.size(); j++)
		{
			approxPolyDP(Mat(contours[j]), contours_poly[j], 3, true);
			boundRect[j] = boundingRect(Mat(contours_poly[j]));
		}

		Mat withRectangles = Mat::zeros(src.size(), CV_8UC3);
		Mat withContours = Mat::zeros(src.size(), CV_8UC3);
		for (auto j = 0; j < contours.size(); j++)
		{
			auto color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));

			drawContours(withContours, contours_poly, j, color, 1, 8, vector<Vec4i>(), 0, Point());
			rectangle(withRectangles, boundRect[j].tl(), boundRect[j].br(), color, 1, 8, 0);
		}

		imshow("Draw rectangles", withRectangles);
		waitKey(1000);
	}

	destroyAllWindows();
	return 0;
}
