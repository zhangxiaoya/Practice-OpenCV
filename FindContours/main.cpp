#include "cv.h"
#include "highgui.h"

using namespace cv;

void DrawSeprateLines(Mat& combinedResult, int imageWidth, int imageHeight)
{
	auto ptr = combinedResult.ptr<Vec3b>(imageHeight);
	for (auto c = 0; c < combinedResult.cols; ++c)
	{
		ptr[c][0] = 255;
		ptr[c][1] = 255;
		ptr[c][2] = 255;
	}
	auto colIdx = imageWidth;
	for (auto r = 0; r < combinedResult.rows; ++r)
	{
		combinedResult.at<Vec3b>(r, colIdx)[0] = 255;
		combinedResult.at<Vec3b>(r, colIdx)[1] = 255;
		combinedResult.at<Vec3b>(r, colIdx)[2] = 255;
	}
}

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

		auto imageHeight = src.rows;
		auto imageWidth = src.cols;

		Mat combinedResult(imageHeight * 2 + 1, imageWidth * 2 + 1, CV_8UC3, Scalar(0));

		DrawSeprateLines(combinedResult, imageWidth, imageHeight);

		auto basicColor = combinedResult(Rect(0, 0, imageWidth, imageHeight));
		cvtColor(src, basicColor, CV_GRAY2RGB);

		auto withField = combinedResult(Rect(0, imageHeight + 1, imageWidth, imageHeight));
		auto withRectangles = combinedResult(Rect(imageWidth + 1, 0, imageWidth, imageHeight));
		auto withContours = combinedResult(Rect(imageWidth + 1, imageHeight + 1, imageWidth, imageHeight));

		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		findContours(src, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

		if (contours.size() == 0)
			continue;

		for (auto idx = 0; idx >= 0; idx = hierarchy[idx][0])
		{
			Scalar color(rand() & 255, rand() & 255, rand() & 255);
			drawContours(withField, contours, idx, color, CV_FILLED, 8, hierarchy);
		}

		vector<vector<Point>> contours_poly(contours.size());
		vector<Rect> boundRect(contours.size());

		for (auto j = 0; j < contours.size(); j++)
		{
			approxPolyDP(Mat(contours[j]), contours_poly[j], 3, true);
			boundRect[j] = boundingRect(Mat(contours_poly[j]));
		}

		for (auto j = 0; j < contours.size(); j++)
		{
			auto color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));

			drawContours(withContours, contours_poly, j, color, 1, 8, vector<Vec4i>(), 0, Point());
			rectangle(withRectangles, boundRect[j].tl(), boundRect[j].br(), color, 1, 8, 0);
		}

		imshow("Combined Result", combinedResult);
		waitKey(1000);
	}

	destroyAllWindows();
	return 0;
}
