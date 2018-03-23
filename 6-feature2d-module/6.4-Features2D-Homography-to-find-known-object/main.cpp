#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/nonfree/nonfree.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    // 读取图像文件
    Mat img1 = imread("/home/runisys/Desktop/data/OpenCVImageData/box.png");
    Mat img2 = imread("/home/runisys/Desktop/data/OpenCVImageData/box_in_scene.png");

    // 判断文件是否读取成功
    if(img1.empty() || img2.empty())
    {
        cout << "Read image files failed" << endl;
        return -1;
    }

    // 检测关键点
    int minHessian = 400;
    SurfFeatureDetector detector(minHessian);

    vector<KeyPoint> keyPoint1;
    vector<KeyPoint> keyPoint2;
    detector.detect(img1, keyPoint1);
    detector.detect(img2, keyPoint2);

    // 计算描述符
    SurfDescriptorExtractor extractor;
    Mat descriptorObject;
    Mat descriptorSence;
    extractor.compute(img1, keyPoint1, descriptorObject);
    extractor.compute(img2, keyPoint2, descriptorSence);

    // 计算算子匹配
    FlannBasedMatcher matcher;
    vector<DMatch> matches;
    matcher.match(descriptorObject, descriptorSence, matches);

    double minDist = 0;
    double maxDist = 100;

    for(int i = 0; i< matches.size(); ++i)
    {
        double dist = matches[i].distance;
        if(dist > minDist)
            minDist = dist;
        if(dist < maxDist)
            maxDist = dist;
    }

    cout << "--Max dist  :" << maxDist << endl;
    cout << "--Min dist  :" << minDist << endl;

    vector<DMatch> goodMatches;

    for(int i = 0; i< matches.size(); ++ i)
    {
        if(matches[i].distance < 3 * minDist)
        {
            goodMatches.push_back(matches[i]);
        }
    }

    Mat matchedImg;
    drawMatches(img1, keyPoint1, img2, keyPoint2, goodMatches, matchedImg, Scalar::all(-1), Scalar::all(-1));

    vector<Point2f> obj;
    vector<Point2f> scense;

    for(int i = 0;i < goodMatches.size(); ++ i)
    {
        obj.push_back(keyPoint1[goodMatches[i].queryIdx].pt);
        scense.push_back(keyPoint2[goodMatches[i].trainIdx].pt);
    }

    Mat H = findHomography(obj, scense,CV_RANSAC);

    vector<Point2f> objCorners(4);
    objCorners[0] = cvPoint(0,0);
    objCorners[1] = cvPoint(img1.cols,0);
    objCorners[2] = cvPoint(img1.cols, img1.rows);
    objCorners[3] = cvPoint(0, img1.rows);

    vector<Point2f> sceneCorners(4);

    perspectiveTransform(objCorners, sceneCorners, H);

    line(matchedImg, sceneCorners[0] + Point2f(img1.cols, 0), sceneCorners[1] + Point2f(img1.cols, 0), Scalar(0, 255, 0),2);
    line(matchedImg, sceneCorners[1] + Point2f(img1.cols, 0), sceneCorners[2] + Point2f(img1.cols, 0), Scalar(0, 255, 0),2);
    line(matchedImg, sceneCorners[2] + Point2f(img1.cols, 0), sceneCorners[3] + Point2f(img1.cols, 0), Scalar(0, 255, 0),2);
    line(matchedImg, sceneCorners[3] + Point2f(img1.cols, 0), sceneCorners[0] + Point2f(img1.cols, 0), Scalar(0, 255, 0),2);
    imshow("Matched Image", matchedImg);
    waitKey(0);

    return 0;
}