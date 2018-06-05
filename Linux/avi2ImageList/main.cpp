#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/video.hpp>
#include <opencv2/highgui.hpp>
#include <iomanip>

int main()
{
    const char* imageListFolder = "/home/runisys/Downloads/text/";
    cv::VideoCapture capture;
    capture.open("/home/runisys/Downloads/text.avi");
    cv::Mat frame;


    int frameId = 0;
    if(capture.isOpened())
    {
        while (true)
        {
            capture >> frame;
            if(frame.empty())
                break;
            std::stringstream ss;
            std::cout << std::setw(6) << frameId << std::endl;
            cv::imshow("Frame", frame);
            ss << imageListFolder << std::setw(6) << std::setfill('0') << frameId << ".png";
            std::cout << "filename is " << ss.str()<<std::endl;
            cv::imwrite(ss.str(), frame);
            cv::waitKey(100);
            ++frameId;
        }
    }
    else
    {
        std::cout << "Unable open avi files" << std::endl;
    }

    cv::destroyAllWindows();
    return 0;
}