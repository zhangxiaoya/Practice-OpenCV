#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat srcImg;
Mat grayImg;

int maxCorners = 23;
int maxTrackbar =100;

RNG rng(12345);
char* sourceWindow = "Image";

void GoodFeaturesToTrackDemo(int, void*);

int main(int argc, char* argv[])
{
    srcImg = imread("/home/runisys/Desktop/data/OpenCVImageData/box.png");
    cvtColor(srcImg, grayImg, CV_RGB2GRAY);

    namedWindow(sourceWindow, 1);
    createTrackbar("Max corner : ", sourceWindow, &maxCorners, maxTrackbar, GoodFeaturesToTrackDemo);

    imshow(sourceWindow, srcImg);

    GoodFeaturesToTrackDemo(0,0);
    waitKey(0);

    return 0;
}

void GoodFeaturesToTrackDemo(int, void*)
{
    if(maxCorners < 1)
    {
        maxCorners = 1;
    }

    vector<Point2f> corners;
    double qualityLevel = 0.001;
    double minDistance = 10;
    int blockSize = 3;
    bool useHarrisDetector = false;
    double K = 0.004;

    Mat copy;
    copy = srcImg.clone();

    goodFeaturesToTrack(grayImg, corners, maxCorners, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, K);

    cout << "** Number of corners detected : " << corners.size() << endl;
    int r = 4;
    for (int i = 0;i< corners.size() ; ++ i)
    {
        circle(copy, corners[i], r,Scalar(rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255)), -1,8, 0);

        namedWindow(sourceWindow, 1);
        imshow(sourceWindow, copy);
    }
}