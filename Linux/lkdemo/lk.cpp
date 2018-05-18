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
    
    return 0;
}