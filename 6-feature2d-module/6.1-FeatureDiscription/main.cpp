#include <iostream>
#include <core/core.hpp>
#include <highgui.h>
#include <nonfree/nonfree.hpp>
#include <features2d/features2d.hpp>

int main(int argc, char* argv[])
{
	cv::Mat img1 = cv::imread("D:\\Bags\\Github\\opencv\\samples\\c\\one_way_train_0000.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat img2 = cv::imread("D:\\Bags\\Github\\opencv\\samples\\c\\one_way_train_0001.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	if(img1.empty() || img2.empty())
	{
		std::cout << "Cannot load image file" << std::endl;
		system("Pause");
		return -1;
	}
	int minHenssian = 400;
	cv::SurfFeatureDetector detector(minHenssian);

	std::vector<cv::KeyPoint> keyPoints1, keyPoints2;
	
	detector.detect(img1, keyPoints1);
	detector.detect(img2, keyPoints2);
	
	cv::SurfDescriptorExtractor extractor;

	cv::Mat descriptors1, descriptors2;
	extractor.compute(img1, keyPoints1, descriptors1);
	extractor.compute(img2, keyPoints2, descriptors2);


	cv::BFMatcher matcher(cv::NORM_L2);
	std::vector<cv::DMatch> matches;
	matcher.match(descriptors1, descriptors2, matches);

	cv::Mat imgMatches;
	drawMatches(img1, keyPoints1, img2, keyPoints2, matches, imgMatches);
	cv::imshow("Matches", imgMatches);
	cv::waitKey(0);

	return 0;
}
