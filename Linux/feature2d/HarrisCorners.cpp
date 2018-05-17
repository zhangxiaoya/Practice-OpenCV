#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cout << "Usage:\n";
        cout <<"\t" << argv[0] << " img" << endl;
        return -1;
    }

    Mat img = imread(argv[1]);
    assert(img.empty());

    imshow("image", img);

    Mat grayImg;
    cvtColor(img, grayImg, CV_RGB2GRAY);

    Mat cornerResult(img.size(), CV_32FC1);
    Mat cornerResultNormalize;
    Mat cornerResultScaled;

    cornerHarris(grayImg, cornerResult, 2, 3, 0.04, BORDER_DEFAULT);

    normalize(cornerResult, cornerResultNormalize, 0, 255, NORM_MINMAX, CV_32FC1);
    convertScaleAbs(cornerResultNormalize, cornerResultScaled);

    for (auto r = 0; r < cornerResultScaled.rows; ++r)
    {
        for (auto c = 0; c < cornerResultScaled.cols; ++c)
        {
            if ((int) cornerResultScaled.at<float>(r, c) > 400)
                circle(cornerResultScaled, Point(c, r), 5, Scalar(0), 2, 8, 0);
        }
    }
    imshow("Corners", cornerResultScaled);
    waitKey(0);
    destroyAllWindows();
    return 0;
}