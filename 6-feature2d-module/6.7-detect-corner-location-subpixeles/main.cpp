#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat srcImg = imread("/home/runisys/Desktop/data/OpenCVImageData/box.png");
    Mat grayImg;
    cvtColor(srcImg, grayImg, CV_RGB2GRAY);

    namedWindow("Image Window", 1);
    vector<Point2f> corners;
    double qualityLevel = 0.01;
    double minDistance = 10;
    int blockSize = 3;
    bool useHarrisDetector = false;

    double K = 0.04;

    RNG rng(12345);

    Mat copy = srcImg.clone();

    goodFeaturesToTrack(grayImg,corners,20,qualityLevel,minDistance,Mat(),blockSize,useHarrisDetector,K);
    cout << "** Number of corners detected: " << corners.size() << endl;

    int r = 4;
    for(int i = 0; i < corners.size(); ++i)
    {
        circle(copy, corners[i], r,Scalar(rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255)),-1,8,0);
    }

    Size winSize(5,5);
    Size zeroZone(-1, -1);
    TermCriteria criteria = TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001);

    cornerSubPix(grayImg,corners,winSize, zeroZone,criteria);

    for(int i = 0; i< corners.size();++i)
    {
        cout << "-- Refined Corner [" << i << "] (" << corners[i].x << "," << corners[i].y << ")" << endl;
    }
    imshow("Image Window", copy);
    waitKey(0);

    return 0;
}