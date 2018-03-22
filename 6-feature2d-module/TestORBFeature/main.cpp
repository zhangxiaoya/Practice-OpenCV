#include <core/core.hpp>
#include <iostream>
#include <vector>
#include <highgui.h>
#include <features2d/features2d.hpp>

int main(int argc, char* argv[])
{
	// ��ȡͼ���ļ�
	cv::Mat img1 = cv::imread("D:\\Bags\\Github\\opencv\\samples\\c\\one_way_train_0000.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat img2 = cv::imread("D:\\Bags\\Github\\opencv\\samples\\c\\one_way_train_0001.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	if(img1.empty() || img2.empty())
	{
		std::cout << "Load image file failed" << std::endl;
		return -1;
	}

	// ���ORB�ؼ���
	std::vector<cv::KeyPoint> keyPoint1;
	std::vector<cv::KeyPoint> keyPoint2;

	cv::OrbFeatureDetector detector;
//	cv::Ptr<cv::OrbFeatureDetector> detector = cv::ORB::create("ORB KeyPoint Detector");
	detector.detect(img1, keyPoint1);
	detector.detect(img2, keyPoint2);

	// ��ȡ������
	cv::Mat descriptor1;
	cv::Mat descriptor2;

	cv::OrbDescriptorExtractor extractor;
//	cv::Ptr<cv::OrbDescriptorExtractor> extractor = cv::ORB::create("ORB Descriptor Extractor");
	extractor.compute(img1, keyPoint1, descriptor1);
	extractor.compute(img2, keyPoint2, descriptor2);

	// ����������
	cv::Mat drawKeyPointResultImg;
	cv::drawKeypoints(img1, keyPoint1, drawKeyPointResultImg);
	cv::imshow("KeyPoints Image", drawKeyPointResultImg);
	cv::waitKey(1);

	// ����ƥ��Ĺؼ���
	std::vector<cv::DMatch> matches;
	cv::BFMatcher matcher;
	matcher.match(descriptor1, descriptor2, matches);

	// ����ƥ��
	cv::Mat drawMatchesResultImg;
	cv::drawMatches(img1, keyPoint1, img2, keyPoint2, matches, drawMatchesResultImg);
	imshow("Matches", drawMatchesResultImg);
	cv::waitKey(0);
	return 0;
}
