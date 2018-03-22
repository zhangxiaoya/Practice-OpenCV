#include <iostream>
#include <core/core.hpp>
#include <highgui.h>
#include <nonfree/nonfree.hpp>
#include <features2d/features2d.hpp>

int main(int argc, char* argv[])
{
	// ��ȡͼ���ļ�
	cv::Mat img1 = cv::imread("D:\\Bags\\Github\\opencv\\samples\\c\\one_way_train_0000.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat img2 = cv::imread("D:\\Bags\\Github\\opencv\\samples\\c\\one_way_train_0001.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	// �ж�ͼ���ļ��Ƿ�Ϊ��
	if(img1.empty() || img2.empty())
	{
		std::cout << "Cannot load image file" << std::endl;
		system("Pause");
		return -1;
	}
	/*
	 * ʹ��Open���SURF�ؼ���
	 */
	auto minHenssian = 400;
	// ����һ��Surf�ؼ��������
	cv::SurfFeatureDetector detector(minHenssian);

	// ���������������ֱ�洢������ͼ������ȡ�Ĺؼ���
	std::vector<cv::KeyPoint> keyPoints1, keyPoints2;

	// Surf�ؼ�����ȡ�����ͼ������ȡ�ؼ��㣬�ֱ�洢�������Ҽ���������
	detector.detect(img1, keyPoints1);
	detector.detect(img2, keyPoints2);

	/*
	 * ��ȡ������
	 */
	// Surf��������ȡ����
	cv::SurfDescriptorExtractor extractor;

	// ���������������Ĵ洢����
	cv::Mat descriptors1, descriptors2;
	// ��ȡSurf������
	extractor.compute(img1, keyPoints1, descriptors1);
	extractor.compute(img2, keyPoints2, descriptors2);

	// ����һ��������ƥ�����
	cv::BFMatcher matcher(cv::NORM_L2);
	// ����һ��ƥ�䵽��������
	std::vector<cv::DMatch> matches;
	// ƥ��������
	matcher.match(descriptors1, descriptors2, matches);

	/*
	 * ����ƥ�������
	 */
	cv::Mat imgMatches;
	drawMatches(img1, keyPoints1, img2, keyPoints2, matches, imgMatches);
	cv::imshow("Matches", imgMatches);
	cv::waitKey(0);

	return 0;
}
