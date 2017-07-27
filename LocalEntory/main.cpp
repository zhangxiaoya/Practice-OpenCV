#include <core/core.hpp>
#include <imgproc/imgproc.hpp>
#include <highgui/highgui.hpp>
#include <iostream>

void do_work(cv::Mat& img)
{
	int frequency[256] = { 0 };
	double probability[256] = { 0.0 };
	double entropy[256] = { 0.0 };

	for (auto r = 0; r < img.rows;++r)
	{
		auto ptr = img.ptr<uchar>(r);
		for (auto c = 0; c < img.cols;++c)
		{
			frequency[static_cast<int>(ptr[c])] ++;
		}
	}

	for (auto i = 0; i < 256;++i)
	{
		probability[i] = static_cast<double>(frequency[i]) / (img.cols * img.rows);
		entropy[i] = log2(probability[i]) * probability[i];
	}
}

int main()
{
	auto img = cv::imread("D:\\Bag\\Code_VS15\\DetectTarget\\DetectTarget\\ir_file_20170531_1000m_1\\Frame_0000.png");

	if(img.empty())
	{
		std::cout << "Read Image File Failed"<<std::endl;
		system("pause");
		return -1;
	}

	do_work(img);

	system("Pause");
	return 0;
}
