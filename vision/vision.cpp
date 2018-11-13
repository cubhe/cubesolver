#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;
VideoCapture capture1(0);
//VideoCapture capture2(1);

/*��ȡһ��ͼ���ڵ���ɫ*/
string ReadOnefaceColor();
/*��ͼ���ϻ���*/
void DrawandCut(Mat & image);
/*�ռ���ɫ*/
void CollectColor(Mat image,Mat &query);

string ReadColor() {
	string color;
	/*���¶���*/
	bool flag = 1;
	while (flag) {
		/*��ȡͼ��*/
		for (size_t i = 0; i < 100; i++) {
			color += ReadOnefaceColor();
		}
		/*�ж��Ƿ����¶���ͼ��*/
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
	//float n = result.at<float>(0, 0);

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
	/*rgb2hsv*/
	Mat hsvimage;
	cvtColor(image, hsvimage, COLOR_RGB2HSV);
	
	float rawdata[9][6] = { 0 };
	int d = 480;
	int cout = 0;
	int dd = d / 3 - 20;//dd=40  
	for (size_t y = 10; y < d; y += d / 3)
	{
		for (size_t x = 10; x < d; x += d / 3) {
			float temp[6];
			for (size_t i = x; i < x+dd; i++){
				for (size_t j = y; j < y+dd; j++){
					for (size_t k = 0; k < 3; k++){
						temp[k] += image.at<cv::Vec3b>(Point(i, j))[k];
						temp[k+3] += hsvimage.at<cv::Vec3b>(Point(i, j))[k];
					}
				}
			}
			rawdata[cout++][6] = temp[6];
		}
	}
	Mat query2(9, 6, CV_32FC1, rawdata);
	query = query2;
}

