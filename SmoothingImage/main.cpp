#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
	auto img = cv::imread("..\\data\\lena.png");
	if(img.empty())
	{
		std::cout << "Read Image File Failed!"<<std::endl;
		system("Pause");
		return -1;
	}
	cv::imshow("current Image", img);
	cv::waitKey(0);

	cv::destroyAllWindows();
	system("Pause");
	return 0;
}
