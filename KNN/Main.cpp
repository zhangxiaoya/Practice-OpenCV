#include <ctime>
#include <cstdio>
#include <iostream>
#include <ml/ml.hpp>
#include <contrib/contrib.hpp>
#include <highgui/highgui.hpp>

int readFlippedInteger(FILE* fp)
{
	auto ret = 0;
	auto temp = reinterpret_cast<uchar*>(&ret);
	fread(&temp[3], sizeof(uchar), 1, fp);
	fread(&temp[2], sizeof(uchar), 1, fp);
	fread(&temp[1], sizeof(uchar), 1, fp);
	fread(&temp[0], sizeof(uchar), 1, fp);
	return ret;
}

int main()
{
	FILE* fp;
	FILE* fp2;
	fopen_s(&fp, "..\\data\\train-images.idx3-ubyte", "rb");
	fopen_s(&fp2, "..\\data\\train-labels.idx1-ubyte", "rb");

	if (!fp || !fp2)
	{
		std::cout << "Files Not Found" << std::endl;
		system("Pause");
		return -1;
	}

	auto magicNumber = readFlippedInteger(fp);
	auto numImages = readFlippedInteger(fp);
	auto numRows = readFlippedInteger(fp);
	auto numCols = readFlippedInteger(fp);

	fseek(fp2, 0x08, SEEK_SET);

	auto size = numRows * numCols;

	cv::Mat trainingVectors(numImages, size, CV_32FC1);
	cv::Mat trainingLabels(numImages, 1, CV_32FC1);

	auto temp = new uchar[size];
	uchar tempClass = 0;

	for (auto i = 0; i < numImages; i++)
	{
		fread(static_cast<void*>(temp), size, 1, fp);
		fread(static_cast<void*>(&tempClass), sizeof(uchar), 1, fp2);
		trainingLabels.at<float>(i, 0) = tempClass;
		cv::Mat img(numRows, numCols, CV_32FC1);
		for (auto k = 0; k < size; k++)
		{
			trainingVectors.at<float>(i, k) = temp[k];
			img.at<float>(k / numCols, k % numCols) = temp[k];
		}
		imshow("data", img);
		cv::waitKey(100);
	}

	cv::KNearest knn(trainingVectors, trainingLabels);
	printf("Maximum k: %d\n", knn.get_max_k());

	fclose(fp);
	fclose(fp2);
	delete[] temp;

	fopen_s(&fp, "..\\data\\t10k-images.idx3-ubyte", "rb");
	fopen_s(&fp2, "..\\data\\t10k-labels.idx1-ubyte", "rb");

	magicNumber = readFlippedInteger(fp);
	numImages = readFlippedInteger(fp);
	numRows = readFlippedInteger(fp);

	numCols = readFlippedInteger(fp);

	fseek(fp2, 0x08, SEEK_SET);
	auto testVectors = cvCreateMat(numImages, size, CV_32FC1);
	auto testLabels = cvCreateMat(numImages, 1, CV_32FC1);
	auto actualLabels = cvCreateMat(numImages, 1, CV_32FC1);
	temp = new uchar[size];
	tempClass = 1;
	auto currentTest = cvCreateMat(1, size, CV_32FC1);
	auto currentLabel = cvCreateMat(1, 1, CV_32FC1);
	auto totalCorrect = 0;

	for (auto i = 0; i < numImages; i++)
	{
		fread(static_cast<void*>(temp), size, 1, fp);

		fread(static_cast<void*>(&tempClass), sizeof(uchar), 1, fp2);

		actualLabels->data.fl[i] = static_cast<float>(tempClass);

		for (auto k = 0; k < size; k++)
		{
			testVectors->data.fl[i * size + k] = temp[k];
			currentTest->data.fl[k] = temp[k];
		}
		knn.find_nearest(currentTest, 5, currentLabel);

		testLabels->data.fl[i] = currentLabel->data.fl[0];

		if (currentLabel->data.fl[0] == actualLabels->data.fl[i])
			totalCorrect++;
	}
	printf("Time: %d Accuracy: %f ", reinterpret_cast<int>(time), static_cast<double>(totalCorrect) * 100 / static_cast<double>(numImages));

	system("Pause");
	return 0;
}
