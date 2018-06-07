#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/video.hpp>
#include <opencv2/highgui.hpp>
#include <iomanip>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << "Usage: \n \t" << argv[0] << " image_folder/ avi_file_name" << std::endl;
        return 1;
    }
    const char *imageListFolder = argv[1];
    cv::VideoCapture capture;
    capture.open(argv[2]);
    if (!capture.isOpened())
    {
        std::cout << "Open AVI file failed!" << std::endl;
        return 2;
    }
    cv::Mat frame;

    int frameId = 0;
    while (true)
    {
        capture >> frame;
        if (frame.empty())
            break;
        std::stringstream ss;
        std::cout << std::setw(6) << frameId << std::endl;
        cv::imshow("Frame", frame);
        ss << imageListFolder  << "/" << std::setw(6) << std::setfill('0') << frameId << ".png";
        std::cout << "filename is " << ss.str() << std::endl;
        cv::imwrite(ss.str(), frame);
        cv::waitKey(100);
        ++frameId;
    }

    cv::destroyAllWindows();
    return 0;
}