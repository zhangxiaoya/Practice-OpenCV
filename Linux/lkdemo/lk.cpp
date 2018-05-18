#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cout << "Usage:\n\t" << argv[0] << " images" << endl;
        return -1;
    }

    VideoCapture capture;
    capture.open(argv[1]);
    if(!capture.isOpened())
    {
        cout << "Open images "<< argv[1] <<" failed" << endl;
        return -1;
    }

    bool isFirstFrame = true;
    Mat frame;
    Mat grayPrev;
    Mat grayCurr;

    vector<Point2f> keyPointCurr;
    vector<Point2f> keyPointPrev;

    int maxCorners = 400;
    double qualityLevel = 0.01;
    double minDistance = 10;
    int size = 3;
    double k = 0.04;

    while (true)
    {
        capture >> frame;
        if(frame.empty())
            break;
        if(frame.type() == CV_8UC3)
            cvtColor(frame, grayCurr, CV_RGB2GRAY);
        else
            grayCurr = frame;

        goodFeaturesToTrack(grayCurr, keyPointCurr, maxCorners, qualityLevel, minDistance, Mat(), size, false, k);

        for(int i = 0; i < keyPointCurr.size(); ++ i)
        {
            circle(frame, keyPointCurr[i], 5,Scalar(0,0,255));
        }

        imshow("Image", frame);
        waitKey(1);
    }

    destroyAllWindows();
    return 0;
}