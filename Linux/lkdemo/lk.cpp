#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video/tracking.hpp>

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

    vector<uchar> status;
    vector<float> error;

    int maxCorners = 400;
    double qualityLevel = 0.01;
    double minDistance = 10;
    int size = 3;
    double k = 0.04;

    Size winSize(21,21);
    TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);

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
        cornerSubPix(grayCurr, keyPointCurr, winSize,Size(-1,-1),termcrit);
        if (grayPrev.empty())
        {
            grayCurr.copyTo(grayPrev);
            keyPointPrev = keyPointCurr;
            continue;
        }

        calcOpticalFlowPyrLK(grayPrev, grayCurr, keyPointPrev, keyPointCurr, status, error);
        int k = 0;
        for (int i = 0; i < status.size(); ++i)
        {
            if (status[i])
            {
                keyPointCurr[k++] = keyPointCurr[i];
            }
        }
        cout << "Keypoint count before LK is " << keyPointCurr.size() << ", after LK is " << k << endl;
        keyPointCurr.resize(k);

        grayCurr.copyTo(grayPrev);
        keyPointPrev = keyPointCurr;

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