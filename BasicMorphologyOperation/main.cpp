#include <iostream>
#include <core/core.hpp>
#include <imgproc/imgproc.hpp>
#include <highgui/highgui.hpp>

auto const MaxElem = 2;
auto const MaxKernelSize = 21;

struct ErosionData
{
	ErosionData() : erosionElem(0), erosionSize(0)
	{
	}
	cv::Mat srcImg;
	int erosionElem;
	int erosionSize;
};

struct DilationData
{
	DilationData() : dilationElem(0), dilationSize(0)
	{
	}

	int dilationElem;
	int dilationSize;
	cv::Mat srcImg;
};

void UpdateErosionView(int erosionType, ErosionData* const data)
{
	auto element = getStructuringElement(erosionType, cv::Size(2 * data->erosionSize + 1, 2 * data->erosionSize + 1), cv::Point(data->erosionSize, data->erosionSize));

	cv::Mat erosionDst;
	erode(data->srcImg, erosionDst, element);
	imshow("Erosion Demo", erosionDst);
}

void Erosion(int, void* data)
{
	auto dataPtr = static_cast<ErosionData*>(data);

	auto erosionType = 0;
	if (dataPtr->erosionElem == 0)
	{
		erosionType = cv::MORPH_RECT;
	}
	else if (dataPtr->erosionElem == 1)
	{
		erosionType = cv::MORPH_CROSS;
	}
	else if (dataPtr->erosionElem == 2)
	{
		erosionType = cv::MORPH_ELLIPSE;
	}

	UpdateErosionView(erosionType, dataPtr);
}

void UpdateDilationView(int dilationType, DilationData* const data)
{
	auto element = getStructuringElement(dilationType, cv::Size(2 * data->dilationSize + 1, 2 * data->dilationSize + 1), cv::Point(data->dilationSize, data->dilationSize));

	cv::Mat dilationDst;
	dilate(data->srcImg, dilationDst, element);
	imshow("Dilation Demo", dilationDst);
}

void Dilation(int, void* data)
{
	auto dataPtr = static_cast<DilationData*>(data);

	auto dilationType = 0;
	if (dataPtr->dilationElem == 0)
	{
		dilationType = cv::MORPH_RECT;
	}
	else if (dataPtr->dilationElem == 1)
	{
		dilationType = cv::MORPH_CROSS;
	}
	else if (dataPtr->dilationElem == 2)
	{
		dilationType = cv::MORPH_ELLIPSE;
	}
	UpdateDilationView(dilationType, dataPtr);
}

void SnapShow(const cv::Mat& img, const char* winname)
{
	cv::namedWindow(winname);
	imshow(winname, img);
	cv::waitKey(0);
	cv::destroyWindow(winname);
}

int main(int argc, char* argv[])
{
	auto img = cv::imread("..\\data\\lena.png");
	if(img.empty())
	{
		std::cout << "Read Image File Failed!" << std::endl;
		system("Pause");
		return -1;
	}

	cv::namedWindow("Erosion Demo", CV_WINDOW_AUTOSIZE);
	cv::namedWindow("Dilation Demo", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("Dilation Demo", img.cols, 0);

	ErosionData erosionData;
	erosionData.srcImg = img;
	DilationData dilationData;
	dilationData.srcImg = img;

	cv::createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo", &(erosionData.erosionElem), MaxElem, Erosion, static_cast<void*>(&erosionData));
	cv::createTrackbar("Kernel size:\n 2n +1", "Erosion Demo", &(erosionData.erosionSize), MaxKernelSize, Erosion, static_cast<void*>(&erosionData));
	cv::createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo", &(dilationData.dilationElem), MaxElem, Dilation,static_cast<void*>(&dilationData));
	cv::createTrackbar("Kernel size:\n 2n +1", "Dilation Demo", &(dilationData.dilationSize), MaxKernelSize, Dilation, static_cast<void*>(&dilationData));

	Erosion(0, static_cast<void*>(&erosionData));
	Dilation(0, static_cast<void*>(&dilationData));
	cv::waitKey(0);

	return 0;
}
