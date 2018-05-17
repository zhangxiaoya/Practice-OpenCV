#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    // 判断参数
    if (argc < 2)
    {
        cout << "Usage:\n";
        cout << "\t" << argv[0] << " img" << endl;
        return -1;
    }

    // 角点检测函数参数设定
    int blockSize = 2;
    int ksize = 3;
    double k = 0.04;

    int threshold = 400;
    if (argc == 3)
        threshold = atoi(argv[2]);
    else
    {
        cout << "Use default threshold " << threshold << endl;
    }

    // 读取图像
    Mat img = imread(argv[1]);

    // 验证图像是否为空
    assert(!img.empty());

    // 显示图像
    imshow("Original Image", img);

    // 转成灰度图
    Mat grayImg;
    if (img.channels() != 1)
        cvtColor(img, grayImg, CV_RGB2GRAY);
    else
        grayImg = img;

    // 中间结果存储
    Mat cornerResult(img.size(), CV_32FC1);
    Mat cornerResultNormalize;
    Mat cornerResultScaled;

    // 使用Harris角点检测函数检测角点
    cornerHarris(grayImg, cornerResult, blockSize, ksize, k, BORDER_DEFAULT);
    // 归一化0到255之间
    normalize(cornerResult, cornerResultNormalize, 0, 255, NORM_MINMAX, CV_32FC1);
    // scales array elements,
    // computes absolute values and converts the results to 8-bit unsigned integers:
    // dst(i)=saturate_cast<uchar>abs(src(i)*alpha+beta)
    // default alpha = 1 and beta = 0
    convertScaleAbs(cornerResultNormalize, cornerResultScaled);

    // 画点的参数
    int radius = 5;
    int thickness = 2;
    int type = 8;
    int shift = 0;

    int cornerCount = 0;

    for (auto r = 0; r < cornerResultScaled.rows; ++r)
    {
        for (auto c = 0; c < cornerResultScaled.cols; ++c)
        {
            if ((int) cornerResultScaled.at<float>(r, c) > threshold)
            {
                circle(img, Point(c, r), radius, Scalar(0, 255, 0), thickness, type, shift);
                cornerCount++;
            }
        }
    }

    cout << "Corner Count is " << cornerCount << endl;
    imshow("Detected Corners", img);

    waitKey(0);
    destroyAllWindows();
    return 0;
}