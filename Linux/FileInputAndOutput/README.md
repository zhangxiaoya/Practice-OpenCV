# 使用FileStorage进行文件读取


OpenCV中使用FIleStorage进行xml和yaml文件读取操作，FileStorage在core模块。使用的时候与普通的文件流一样，需要打开一个文件，进行读或者写，以及append模式。文件扩展名可以是xml或者yaml，但是只能是一个，默认是yaml。

与普通的文件流不同的是：

文件形式不再是单纯的纯文本，而是有两种数据结构，分别是mapping和sequence。前者类似于STL中的map，后者类似于vector。

## 1 文件格式
**打开文件**
```
string filename = "I.xml";
FileStorage fs(filename,FileStorage::WRITE);

fs.open(filename, FileStorage::READ);
```
要是把文件名写成压缩文件扩展名，还能自动压缩。

**关闭文件**
fs.release();

## 2 读取、写入文本或者数字
**向文件中写入数字**
```
fs << "Key" << 100;
```

**从文件中读取数字**
```
int itNr;
fs["Key"] >> itNr;
// or
itNr = static_cast<int>(fs["Key"]);
```
## 3 读取内置数据结构

```
Mat R = Mat_<uchar>::eye(3,3);
Mat T = Mat_<uchar>::zeros(3,3);

fs << "R" << R;
fs << "T" << T;

fs["R"] >> R;
fs["T"] >> T;
```

## 4 读取序列或者映射

**序列写入**
写入序列是用的"[]"

```
fs << "strings" << "[";
fs << "image1.jpg" << "Awesomeness" << "baboon.jpg";
fs << "]";
```

**映射写入**
写入映射是用的“{}”

```
fs << "mapping";
fs << "{" << "One" << 1;
fs << "Two" << 2;
fs << "}";
```

**序列读取**
读取的序列存储在FileNode中，或者使用FileNodeIterator进行遍历。
```
FileNode n = fs["strings"];
if(n.type() != FileNode::SEQ)
{
    cerr << " strings is not a sequence! FAIL" << endl;
    return -1;
}

FileNodeIterator it = n.begin(), it_end = n.end();
for(; it != it_end; it++)
{
    cout << static_cast<string>(*it) << endl;
}
```

**映射读取**

使用类似于Map的方式读取映射

```
n = fs["mapping"];
cout << "Two" << static_cast<int>(n["Two"]) << ";";
cout << "One" << static_cast<int>(n["One"]) << endl << endl;
```

## 5 读取自定义数据类型

自定义的数据类型，需要在类的内部自定义序列化输入输出的函数，另外，还需要在类外定义FileStorage的读取和写入的函数：
```
static void read(const cv::FileNode &node, MyData& x, const MyData &default_value = MyData())

static void write(cv::FileStorage &fs, const std::string &, const MyData &x);
```

这两个函数主要是对于写入和读取自定义类的序列化， 在使用FileStorage对象进行自定义数据类型进行读取和写入操作的时候，调用这两个重载函数。

## 参考

[https://docs.opencv.org/ref/2.4.13.5/da/d56/classcv_1_1FileStorage.html](https://docs.opencv.org/ref/2.4.13.5/da/d56/classcv_1_1FileStorage.html)