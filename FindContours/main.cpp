#include <iostream>
#include <highgui/highgui.hpp>

int main(int argc, char* argv[])
{
	auto img = cv::imread("..\\data\\lena.png");
	if(img.empty() == true)
	{
		std::cout << "Read Image File Failed!" << std::endl;;
		system("Pause");
		return -1;
	}
	imshow("Original Image", img);
	cv::waitKey(0);
	cv::destroyAllWindows();
	system("Pause");
	return 0;
}
