#include <core/core.hpp>
#include <highgui.h>
#include <video/video.hpp>

int main(int argc, char* argv[])
{
	cv::Mat srcImg = cv::imread("..\\..\\data\\lena.png");
	if(srcImg.empty() == true)
	{
		system("Pause");
		return -1;
	}

	/// Brief how-to for this program
	printf("\n \t copyMakeBorder Demo: \n");
	printf("\t -------------------- \n");
	printf(" ** Press ¡¯c¡¯ to set the border to a random constant value \n");
	printf(" ** Press ¡¯r¡¯ to set the border to be replicated \n");
	printf(" ** Press ¡¯ESC¡¯ to exit the program \n");

	int top = static_cast<int>(0.05 * srcImg.rows);
	int bottom = static_cast<int>(0.05 * srcImg.rows);
	int left = static_cast<int>(0.05 * srcImg.cols);
	int right = static_cast<int>(0.05 * srcImg.cols);

	cv::Mat dstImg = srcImg;
	char* WindowName = "Image Name";
	cv::namedWindow(WindowName);

	cv::RNG rng(12345);
	cv::Scalar value;

	int borderType = cv::BORDER_REPLICATE;
	while (true)
	{
		int key = cv::waitKey(10);
		if(key == 27)
		{
			break;
		}
		if(static_cast<char>(key) == 'r')
		{
			borderType = cv::BORDER_REPLICATE;
		}
		else if(static_cast<char>(key) == 'c')
		{
			borderType = cv::BORDER_CONSTANT;
		}
		value = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		cv::copyMakeBorder(srcImg, dstImg, top, bottom, left, right, borderType, value);
		cv::imshow(WindowName, dstImg);
	}
		
	return 0;
}
