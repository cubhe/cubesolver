#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;
VideoCapture capture1(0);
//VideoCapture capture2(1);

string ReadOnefaceColor();
void DrawandCut(Mat & image);
void CollectColor(Mat image,Mat &query);

string ReadColor() {
	string color;
	/*重新读入*/
	bool flag = 1;
	while (flag) {
		/*读取图像*/
		for (size_t i = 0; i < 100; i++) {
			color += ReadOnefaceColor();
		}
		/*判断是否重新读入图像*/
		flag = 0;
	}
	return color;
}
string ReadOnefaceColor() {
	string color;
	Mat image_read1,image_read2;
	capture1 >> image_read1;
	cout << image_read1.size << endl;
	//capture2 >> image_read2;
	DrawandCut(image_read1);
	//DrawandCut(image_read2);

	Ptr<ml::SVM>svm = ml::SVM::load("color.xml");
	Mat query,result;
	CollectColor(image_read1, query);
	svm->predict(query, result);
	float n = result.at<float>(0, 0);

	imshow("umm", image_read1);
	//imshow("ummm", image_read2);
	waitKey(0);
	return color;
}
void DrawandCut(Mat & image) {
	int a = 0, b = 0, c = 0, d = 480;
	image = image(  Rect(Point(0, 0), Point(d, d))  );
	int dd = d / 3 - 20;//dd=40  
	for (size_t y = 10; y < d; y+=d/3)
	{
		for (size_t x = 10; x < d; x += d / 3) {
			if (x != (10 + d / 3) || y != (10 + d / 3)) {
				rectangle(image, Point(x, y), Point(x + dd, y + dd), Scalar(a, b, c), 2, 8, 0);
			}
			else {
				circle(image, Point(d/2, d/2), dd/2, Scalar(a, b, c), 2);
			}
		}
	}
}
void CollectColor(Mat image, Mat &query) {

	//Mat query(9, 6, CV_32FC1, dig);

}

