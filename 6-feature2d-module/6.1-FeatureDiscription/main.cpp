#include <iostream>
#include <core/core.hpp>
#include <highgui.h>
#include <nonfree/nonfree.hpp>
#include <features2d/features2d.hpp>

int main(int argc, char* argv[])
{
	// 读取图像文件
	cv::Mat img1 = cv::imread("D:\\Bags\\Github\\opencv\\samples\\c\\one_way_train_0000.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat img2 = cv::imread("D:\\Bags\\Github\\opencv\\samples\\c\\one_way_train_0001.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	// 判断图像文件是否为空
	if(img1.empty() || img2.empty())
	{
		std::cout << "Cannot load image file" << std::endl;
		system("Pause");
		return -1;
	}
	/*
	 * 使用Open检测SURF关键点
	 */
	auto minHenssian = 400;
	// 定义一个Surf关键点检测对象
	cv::SurfFeatureDetector detector(minHenssian);

	// 定义两个向量，分别存储从两幅图像中提取的关键点
	std::vector<cv::KeyPoint> keyPoints1, keyPoints2;

	// Surf关键点提取对象从图像中提取关键点，分别存储在两个挂件点向量中
	detector.detect(img1, keyPoints1);
	detector.detect(img2, keyPoints2);

	/*
	 * 提取描述符
	 */
	// Surf描述符提取对象
	cv::SurfDescriptorExtractor extractor;

	// 定义两个描述符的存储矩阵
	cv::Mat descriptors1, descriptors2;
	// 提取Surf描述符
	extractor.compute(img1, keyPoints1, descriptors1);
	extractor.compute(img2, keyPoints2, descriptors2);

	// 定义一个描述符匹配对象
	cv::BFMatcher matcher(cv::NORM_L2);
	// 定义一个匹配到的描述符
	std::vector<cv::DMatch> matches;
	// 匹配描述子
	matcher.match(descriptors1, descriptors2, matches);

	/*
	 * 画出匹配的描述
	 */
	cv::Mat imgMatches;
	drawMatches(img1, keyPoints1, img2, keyPoints2, matches, imgMatches);
	cv::imshow("Matches", imgMatches);
	cv::waitKey(0);

	return 0;
}
