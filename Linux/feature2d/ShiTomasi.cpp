#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Usage:\n\t" << argv[0] << " img" << std::endl;
        return -1;
    }

    // 角点检测参数
    int MaxCornerCount = 200;
    double qualityLevel = 0.01;
    int minDistance = 10;
    int blockSize = 3;
    bool useHarrisDetector = false;
    double k = 0.04;

    if(argc == 3)
    {
        MaxCornerCount = atoi(argv[2]);
    }
    else
    {
        cout << "Use default max corner count " << MaxCornerCount << endl;
    }

    // 读取图像并检测是否为空
    Mat img = imread(argv[1]);
    assert(!img.empty());

    Mat grayImg;
    if (img.channels() == 3)
    {
        cvtColor(img, grayImg, CV_RGB2GRAY);
    } else
    {
        grayImg = img;
    }
    imshow("Original image", img);

    vector<Point2f> corners;
    
    goodFeaturesToTrack(grayImg, corners, MaxCornerCount, qualityLevel, minDistance, Mat(), blockSize,
                        useHarrisDetector, k);

    // 画图参数
    int radius = 5;
    int thickness = 1;
    int type = 8;
    int shift = 0;

    for (auto i = 0; i < corners.size(); ++i)
    {
        circle(img, corners[i], radius, Scalar(0, 255, 0), thickness, type, shift);
    }
    cout << "Detect corner count is " << corners.size() << endl;
    imshow("Corners", img);

    waitKey(0);
    destroyAllWindows();
    return 0;
}