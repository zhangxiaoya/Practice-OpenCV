/*
** This is use OpenCV 3.2.0
*/

#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
// NOTE: it is diffrent from Opencv 2.4*
#include <opencv2/xfeatures2d/nonfree.hpp>

using namespace cv;
using namespace cv::xfeatures2d;

int main()
{
    // 读取图片
    Mat img1 = imread("/home/runisys/Desktop/data/OpenCVImageData/one_way_train_0000.jpg");
    Mat img2 = imread("/home/runisys/Desktop/data/OpenCVImageData/one_way_train_0001.jpg");

    // 检查图像是否读取成功
    if(img1.empty() || img2.empty())
    {
        std::cout << "Read image files failed!" << std::endl;
        return -1;
    }

    // 第一，检测关键点
    int minHessian = 400;
    Ptr<SURF> detector = SURF::create(minHessian);

    std::vector<KeyPoint> keyPoint1;
    std::vector<KeyPoint> keyPoint2;

    Mat descriptor1;
    Mat descriptor2;    

    // detector->detect(img1, keyPoint1);
    // detector->detect(img2, keyPoint2);

    // 第二，计算描述符
    // detector->compute(img1, keyPoint1, descriptor1);
    // detector->compute(img2, keyPoint2, descriptor2);

    // 或者可以直接全部计算
    detector->detectAndCompute(img1, Mat(), keyPoint1, descriptor1);
    detector->detectAndCompute(img2, Mat(), keyPoint2, descriptor2);

    // 第三，使用FLANN匹配描述符
    FlannBasedMatcher matcher;
    std::vector<DMatch> matches;
    matcher.match(descriptor1,descriptor2, matches);

    double maxDist = 0;
    double minDist = 100;

    for(int i = 0; i < descriptor1.rows; ++i)
    {
        double dist = matches[i].distance;
        if(dist < minDist)
            minDist = dist;
        if(dist > maxDist)
            maxDist = dist;
    }

    std::cout << "-- Max dist : " << maxDist << std::endl;
    std::cout << "-- Min dist : " << minDist << std::endl;

    std::vector<DMatch> goodMatches;
    for(int i = 0; i < descriptor1.rows; ++i)
    {
        if(matches[i].distance <= max(2*minDist, 0.02))
        {
            goodMatches.push_back(matches[i]);
        }
    }

    Mat goodMatchedResultImg;
    drawMatches(img1, keyPoint1, img2, keyPoint2, goodMatches, goodMatchedResultImg, Scalar::all(-1));

    imshow("Good Matches", goodMatchedResultImg);
    for(int i = 0; i < goodMatches.size(); ++i)
    {
        std::cout <<  "-- Good Match [" << i << "] KeyPoint 1 : " << goodMatches[i].queryIdx << " -- KeyPoint 2 : " << goodMatches[i].trainIdx << std::endl;
    }
    waitKey(0);
    return 0;
}