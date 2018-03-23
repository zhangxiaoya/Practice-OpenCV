#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <highgui.h>

using namespace std;
using namespace cv;


Mat srcImg;
Mat grayImg;

Mat myHarrisDst;
Mat myHarrisCopy;
Mat Mc;

Mat myShiTomasiDst;
Mat myShiTamosiCopy;

int myShiTomasiQulityLevel = 50;
int myHarrisQualityLevel = 50;
int maxQualityLevel = 100;

double myHarrisMinVal;
double myHarrisMaxVal;
double myShiTamosiMinVal;
double myShiTamosiMaxVal;

RNG rng(12345);

const char* myHarrisWindows = "My Harris Corner Detector";
const char* myShiTamosiWiddows = "My Shi Tamoshi Detector";

void myShiTamosiFunc(int ,void*);

void myHarrisFunc(int ,void*);

int main()
{
    srcImg = imread("/home/runisys/Desktop/data/OpenCVImageData/box.png");
    cvtColor(srcImg, grayImg, CV_RGB2GRAY);

    int blockSize = 3;
    int apertureSize = 3;

    myHarrisDst = Mat::zeros(grayImg.size(), CV_32FC(6));
    Mc = Mat::zeros(grayImg.size(), CV_32FC1);

    cornerEigenValsAndVecs(grayImg, myHarrisDst, blockSize, apertureSize, BORDER_DEFAULT);

    for(int j = 0; j < grayImg.rows; ++ j)
    {
        for(int i = 0;i < grayImg.cols; ++i)
        {
            float lambda_1 = myHarrisDst.at<Vec6f>(j,i)[0];
            float lambda_2 = myHarrisDst.at<Vec6f>(j,i)[1];
            Mc.at<float>(j,i) = lambda_1 * lambda_2 - 0.04f * pow((lambda_1 + lambda_2), 2);
        }
    }

    minMaxLoc(Mc, &myHarrisMinVal, &myHarrisMaxVal, 0,0, Mat());

    namedWindow(myHarrisWindows, 1);
    createTrackbar("QualityLevel :", myHarrisWindows, &myHarrisQualityLevel, maxQualityLevel, myHarrisFunc);
    myHarrisFunc(0,0);
    waitKey(0);

    myShiTomasiDst = Mat::zeros(grayImg.size(), CV_32FC1);
    cornerMinEigenVal(grayImg, myShiTomasiDst, blockSize, apertureSize, BORDER_DEFAULT);

    minMaxLoc(myShiTomasiDst, &myShiTamosiMinVal, &myShiTamosiMaxVal, 0,0, Mat());
    namedWindow(myShiTamosiWiddows,1);

    createTrackbar("Quality Level:", myShiTamosiWiddows, &myShiTomasiQulityLevel, maxQualityLevel, myShiTamosiFunc);
    myShiTamosiFunc(0,0);

    waitKey(0);

    return 0;
}

void myShiTamosiFunc(int, void *)
{
    myShiTamosiCopy = srcImg.clone();
    if(myShiTomasiQulityLevel < 1)
    {
        myShiTomasiQulityLevel =1;
    }
    for(int j = 0; j < grayImg.rows; ++j)
    {
        for(int i = 0; i < grayImg.cols; ++ i)
        {
            if(myShiTomasiDst.at<float>(j,i) >myShiTamosiMinVal + (myShiTamosiMaxVal - myShiTamosiMinVal) * myShiTomasiQulityLevel / maxQualityLevel)
            {
                circle(myShiTamosiCopy, Point(i,j), 4, Scalar(rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255)));
            }
        }
    }
    imshow(myShiTamosiWiddows, myShiTamosiCopy);
}

void myHarrisFunc(int, void *)
{
    myHarrisCopy = grayImg.clone();
    if(myHarrisQualityLevel < 1)
    {
        myHarrisQualityLevel = 1;
    }

    for(int j = 0; j< grayImg.rows; ++j)
    {
        for(int i = 0; i< grayImg.cols; ++ i)
        {
            if(Mc.at<float>(j,i) > myHarrisMinVal + (myHarrisMaxVal - myHarrisMinVal) *  myHarrisQualityLevel /maxQualityLevel)
            {
                circle(myHarrisCopy, Point(i,j), 4, Scalar(rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255)));
            }
        }
    }
    imshow(myHarrisWindows, myHarrisCopy);
}
