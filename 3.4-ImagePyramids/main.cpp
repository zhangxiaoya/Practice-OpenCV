#include <iostream>
#include <opencv2/core/core.hpp>
#include <highgui.h>
#include <contrib/contrib.hpp>

int main(int argc, char* argv[])
{
	cv::Mat srcImg;
	cv::Mat dstImg;
	cv::Mat tmpImg;

	printf("\n Zoom In-Out demo          \n");
	printf("-----------------------------\n");
	printf(" * [u] -> Zoom in            \n");
	printf(" * [d] -> Zoom out            \n");
	printf(" * [ESC] -> Close Program \n \n");

	srcImg = cv::imread("..\\data\\lena.png");
	if(srcImg.empty() == true)
	{
		std::cout << "Cannot open image file" << std::endl;
		system("Pause");
		return -1;
	}

	tmpImg = srcImg;
	dstImg = tmpImg;

	auto winname = "Original Image";

	cv::namedWindow(winname, CV_WINDOW_AUTOSIZE);

	while(true)
	{
		int key = cv::waitKey(10);
		if(key == 27)
		{
			break;
		}
		if(static_cast<char>(key) == 'u')
		{
			// maybe change default parameters
			cv::pyrUp(tmpImg, dstImg, cv::Size(tmpImg.cols * 2, tmpImg.rows * 2));
			printf("** Zoom In: Image * 2 \n");
		}
		else if(static_cast<char>(key) == 'd')
		{
			// maybe change default parameters
			cv::pyrDown(tmpImg, dstImg, cv::Size(tmpImg.cols / 2, tmpImg.rows / 2));
			printf("** Zoom Out: Image / 2 \n");
		}
		cv::imshow(winname, dstImg);
		tmpImg = dstImg;
	}

	system("Pause");
	return 0;
}
