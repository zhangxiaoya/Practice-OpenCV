#include <iostream>
#include <opencv2/core.hpp>
#include <string>

// 自定义数据结构
class MyData
{
public:
    MyData() : A(0), X(0), id() {}

    explicit MyData(int) : A(97), X(CV_PI), id("mydata1234") {}

    // 自定义写序列化函数
    void write(cv::FileStorage &fs) const
    {
        fs << "{" << "A" << A << "X" << X << "id" << id << "}";
    }

    // 自定义读序列化函数
    void read(const cv::FileNode &node)
    {
        A = static_cast<int>(node["A"]);
        X = static_cast<double>(node["X"]);
        id = static_cast<std::string>(node["id"]);
    }

public:
    int A;
    double X;
    std::string id;
};

// 对应与使用FileStorage进行write, fs << "some string" << x, 把 x 写入到文件中
static void write(cv::FileStorage &fs, const std::string &, const MyData &x)
{
    x.write(fs);
}

// 对应于适应FileStorage进行read, fs["some string"] >> x, 从文件中读取数据存储到x中
static void read(const cv::FileNode &node, MyData& x, const MyData &default_value = MyData())
{
    if (node.empty())
        x = default_value;
    else
        x.read(node);
}

// 重载输出流对象，用于输出自定义数据结构
static std::ostream &operator<<(std::ostream &out, const MyData &m)
{
    out << "{id = " << m.id << ", ";
    out << "X = " << m.X << ", ";
    out << "A = " << m.A << "}";
    return out;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Must have one parameter" << std::endl;
        return -1;
    }
    std::string filename = argv[1];
    {
        std::cout << "Writing to FileStorage" << std::endl;
        cv::Mat R = cv::Mat_<uchar>::eye(3, 3);
        cv::Mat T = cv::Mat_<uchar>::zeros(3, 3);
        MyData m(1);
        cv::FileStorage fs(filename, cv::FileStorage::WRITE);

        fs << "iterationNr" << 100;
        fs << "strings" << "[";
        fs << "image1.jpg" << "Awesomess" << "baboon.jpg";
        fs << "]";

        fs << "Mapping";
        fs << "{" << "One" << 1;
        fs << "Two" << 2 << "}";

        fs << "R" << R;
        fs << "T" << T;

        fs << "MyData" << m;
        std::cout << "Write Done." << std::endl;
        fs.release();
    }
    {
        std::cout << std::endl << "Reading: " << std::endl;
        cv::FileStorage fs;
        fs.open(filename, cv::FileStorage::READ);

        int itNr;
        itNr = static_cast<int>(fs["iterationNr"]);
        std::cout << "iterationNr " << itNr;
        if (!fs.isOpened())
        {
            std::cerr << "Failed to open " << filename << std::endl;
            return -1;
        }
        cv::FileNode n = fs["strings"];
        if (n.type() != cv::FileNode::SEQ)
        {
            std::cerr << "strings is not a sequence! FAIL" << std::endl;
            return -1;
        }

        cv::FileNodeIterator it = n.begin();
        cv::FileNodeIterator it_end = n.end();
        for (; it != it_end; ++it)
        {
            std::cout << static_cast<std::string>(*it) << std::endl;
        }

        n = fs["Mapping"];
        std::cout << "Two " << static_cast<int>(n["Two"]) << "; ";
        std::cout << "One " << static_cast<int>(n["One"]) << std::endl << std::endl;

        MyData m;
        cv::Mat R, T;

        fs["R"] >> R;
        fs["T"] >> T;
        fs["MyData"] >> m;

        std::cout << std::endl
                  << "R = " << R << std::endl;
        std::cout << "T = " << T << std::endl;
        std::cout << "MyData = " << std::endl << m << std::endl << std::endl;

        std::cout << "Attempt to read NonExisting (should initialize the data structure with its default";
        fs["NonExisting"] >> m;
        std::cout << std::endl << "NonExisting = " << std::endl << m << std::endl;
        fs.release();
    }
    std::cout << std::endl
              << "Tip: Open up "
              << filename
              << " with a text editor to see the serialized data."
              << std::endl;
    return 0;
}