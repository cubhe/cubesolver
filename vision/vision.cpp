#include<opencv2/ml.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv.hpp>
#include<iostream>
#include<string>
#include"SerialPort.h"
using namespace cv;
using namespace cv::ml;
using std::cout;
using std::endl;
using std::string;
char type2col(int n);
string WriteColor(Mat & srcimage, Mat& hsvimage);
void output(CSerialPort & mySerialPort) {
	unsigned char a = static_cast<char>('a');
	if (!mySerialPort.WriteData(&a, 1)) {
		std::cout << "WriteData fail !" << std::endl;
	}
	else {
		std::cout << "WriteData success !" << std::endl;
	}
}
string vision() {


	system("color 80");
	Mat srcimage;
	Mat hsvimage;
	string col("");
	VideoCapture capture(1);
	CSerialPort mySerialPort;
	if (!mySerialPort.InitPort(6)) {
		std::cout << "initPort fail !" << std::endl;
	}
	if (!mySerialPort.OpenListenThread()) {
		std::cout << "OpenListenThread fail !" << std::endl;
	}
	capture >> srcimage;
	output(mySerialPort);
	for (int face = 0; face < 6; face++) {
		for (size_t i = 0; i < 20; i++) {
			capture >> srcimage;
			srcimage = srcimage(Rect(Point(150 + 70 + 20, 50 + 90 + 20), Point(400 + 30 + 20, 300 + 50 + 20)));
			line(srcimage, Point(70, 0), Point(70, 210), Scalar(0, 0, 0));
			line(srcimage, Point(70 * 2, 0), Point(70 * 2, 210), Scalar(0, 0, 0));
			line(srcimage, Point(0, 70), Point(210, 70), Scalar(0, 0, 0));
			line(srcimage, Point(0, 140), Point(210, 140), Scalar(0, 0, 0));
			imshow("原始图像", srcimage);
			waitKey(15);
		}
		imwrite("emm.jpg", srcimage);
		cvtColor(srcimage, hsvimage, CV_RGB2HSV);
		GaussianBlur(srcimage, srcimage, Size(9, 9), 0, 0);
		col += WriteColor(srcimage, hsvimage);
		imshow("原始图像", srcimage);
		output(mySerialPort);
		if (face == 3)
			waitKey(800);
	}
	//output(mySerialPort);
	return col;
}
string WriteColor(Mat & srcimage, Mat & hsvimage) {
	Ptr<ml::SVM>svm = ml::SVM::load("color.xml");
	Mat result;
	const int d = 70;
	string color = "";
	float testData[(50 * 50)][6] = { { 0,0,0,0,0,0 } };
	for (int x0 = 0; x0 < 3; x0++) {
		for (int y0 = 0; y0 < 3; y0++) {
			//x0 = 2; y0 = 1;
			int number = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0;
			//50
			if (x0 == 2 && y0 == 1) {
				x1 = d * x0 + 10;
				y1 = d * y0 + 10;
				x2 = d * (x0 + 1) - 10 - 25;
				y2 = d * (y0 + 1) - 10;
			}
			else if (x0 == 1 && y0 == 0) {
				x1 = d * x0 + 10;
				y1 = d * y0 + 10 + 25;
				x2 = d * (x0 + 1) - 10;
				y2 = d * (y0 + 1) - 10;

			}
			else {
				x1 = d * x0 + 10;
				y1 = d * y0 + 10;
				x2 = d * (x0 + 1) - 10;
				y2 = d * (y0 + 1) - 10;
			}
			for (int x = x1; x <x2; x++) {
				for (int y = y1; y < y2; y++) {
					if (hsvimage.at<cv::Vec3b>(x, y)[0]<3 && hsvimage.at<cv::Vec3b>(x, y)[1]<3)
					{
						for (size_t i = 0; i < 6; i++) {
							testData[number][i] = 0;
						}
					}
					else
					{
						for (size_t j = 0; j < 3; j++) {
							testData[number][j] = srcimage.at<cv::Vec3b>(x, y)[j];
							testData[number][j + 3] = hsvimage.at<cv::Vec3b>(x, y)[j];
							srcimage.at<cv::Vec3b>(x, y)[j] = 255;
						}

					}
					number++;
				}
			}
			for (size_t i = number; i < 2500; i++)
			{
				for (size_t j = 0; j < 6; j++) {
					testData[i][j] = 0;
				}
			}
			//URFDLB WRGYOB 123456 遵循某种玄学
			Mat query((50 * 50), 6, CV_32FC1, testData);
			svm->predict(query, result);
			float n = result.at<float>(0, 0);
			int type[7] = { 0,0,0,0,0,0,0 };
			//cout << result.channels() << endl;
			//计数
			for (size_t i = 0; i < (50 * 50); i++) {
				//G 红色小于60
				if (static_cast<long>(result.at<float>(i, 0)) == 2 || static_cast<long>(result.at<float>(i, 0)) == 5) {
					//if (testData[i][5]<140 && testData[i][5]>30) {
					//	type[1]++;
					//}
					//else if (testData[i][5]>150) {
					//	type[4]++;
					//}

					if (testData[i][1]<70 && testData[i][1]>0) {
						type[1]++;
					}
					else if (testData[i][5]>80) {
						type[4]++;
					}

				}
				else if (static_cast<long>(result.at<float>(i, 0)) == 3 || static_cast<long>(result.at<float>(i, 0)) == 4) {
					//红色通道 小于90绿色 大于150黄色
					if (testData[i][2] < 90) {
						type[2]++;
					}
					else if (testData[i][2] > 150) {
						type[3]++;
					}
				}
				else {
					type[static_cast<long>(result.at<float>(i, 0)) - 1]++;
				}

				/*cout << '{';
				for (size_t j = 0; j < 6; j++)
				{
				cout << testData[i][j] << ',';
				}
				cout << '}';
				cout << result.at<float>(i, 0) << ' ';*/
			}
			//cout << endl << endl;
			//直观
			for (size_t i = 0; i < 7; i++) {
				if (type[i]) {
					cout << i + 1 << ' ' << type[i] << ' ';
				}
			}
			cout << ',';
			//加入col
			int bigest = 0;
			int two = 0;
			for (size_t i = 0; i < 6; i++) {
				if (type[bigest] <= type[i]) {
					bigest = i;
				}
			}
			for (size_t i = 0; i < 6; i++) {
				if (i != bigest && type[two] <= type[i]) {
					two = i;
				}
			}
			if (bigest - two < 20) {
				color += type2col(bigest + 1);
			}
			else {
				color += ' ';
			}

		}
		cout << endl;
	}
	cout << endl << endl;
	cout << color << endl << endl;
	return color;
}
char type2col(int n) {
	//URFDLB WRGYOB 123456 遵循某种玄学
	int x = 0, y = 0;
	if (n == 1) {
		//putText(srcimage, "White", Point(x, y), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2, 8);
		//cout << "W";		
		return 'W';
	}
	else if (n == 4) {
		//putText(srcimage, "Yellow", Point(x, y), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2, 8);
		//cout << "Y";		
		return 'Y';
	}
	else if (n == 5) {
		//putText(srcimage, "Orange", Point(x, y), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2, 8);
		//cout << "O";		
		return 'O';
	}
	else if (n == 2) {
		//putText(srcimage, "Red", Point(x, y), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2, 8);
		//cout << "R";		
		return 'R';
	}
	else if (n == 3) {
		//putText(srcimage, "Green", Point(x, y), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2, 8);
		//cout << "G";		
		return 'G';
	}
	else if (n == 6) {
		//putText(srcimage, "Blue", Point(x, y), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2, 8);
		//cout << "B";		
		return 'B';
	}
	else {
		cout << " ";		return ' ';
	}
}
void training() {
	//URFDLB W1 R2 G3 Y4 O5 B6 123456 遵循某种玄学
	//训练需要用到的数据  
	int lable[54 + 54 + 54 + 9 + 20 + 54 + 4] = {

		5,5,1,1,3,5,2,1,6,
		5,5,4,1,5,6,3,3,3,
		4,2,6,4,6,5,3,3,1,
		3,1,2,3,2,6,2,6,5,
		6,6,1,4,1,4,2,3,6,
		1,2,4,2,4,4,4,2,5,

		4,1,4,3,3,1,6,4,5,
		2,5,6,4,5,1,6,2,5,
		3,6,6,5,6,3,1,2,1,
		2,5,5,2,2,6,3,4,3,
		5,4,4,5,1,1,3,3,1,
		4,2,2,6,4,6,1,3,2,

		2,2,3,6,3,5,3,5,6,
		4,3,3,3,5,2,2,3,1,
		1,5,3,2,6,1,6,4,6,
		5,1,5,6,2,3,5,1,2,
		1,4,2,4,1,4,4,6,6,
		4,2,4,1,4,6,5,5,1,

		2,2,2,2,2,2,2,2,2,

		7,7,7,7,7,7,7,7,7,7,
		7,7,7,7,7,7,7,7,7,7,

		2,2,4,3,2,4,1,5,5,
		5,4,2,6,6,2,3,6,2,
		4,3,5,3,5,1,3,1,4,
		1,5,1,2,3,1,3,3,5,
		6,5,6,4,1,2,6,6,6,
		3,6,4,4,4,1,2,5,1,

		2,2,5,5
	};
	float trainingdata[310][6] = {
		{ 11,95,245,109,243,245 },{ 7,96,245,108,247,245 },{ 206,190,185,7,25,206 },{ 153,142,136,7,22,153 },{ 73,171,7,48,243,171 },{ 5,99,245,108,248,245 },{ 0,3,112,118,254,112 },{ 193,178,171,9,29,193 },{ 192,61,6,8,246,192 },

	{ 8,92,245,109,246,245 },{ 11,97,245,109,243,245 },{ 106,218,170,76,131,218 },{ 155,142,137,6,24,155 },{ 8,101,248,108,246,248 },{ 199,68,6,9,246,199 },{ 62,156,2,48,251,156 },{ 71,159,8,47,242,159 },{ 78,170,10,47,238,170 },

	{ 100,211,164,77,133,211 },{ 0,9,135,118,253,135 },{ 199,66,4,9,248,199 },{ 77,164,128,63,110,164 },{ 200,69,7,9,244,200 },{ 14,102,245,108,239,245 },{ 69,159,9,47,239,159 },{ 72,164,12,48,235,164 },{ 211,191,187,5,28,211 },

	{ 78,168,11,47,237,168 },{ 211,194,187,8,28,211 },{ 0,7,133,118,254,133 },{ 55,128,5,39,199,128 },{ 0,9,135,117,254,135 },{ 206,69,2,9,251,206 },{ 0,3,115,119,254,115 },{ 188,61,6,9,246,188 },{ 11,102,245,108,243,245 },

	{ 187,59,6,8,246,187 },{ 194,65,7,9,245,194 },{ 209,191,192,95,22,209 },{ 74,161,126,63,112,161 },{ 213,194,193,53,23,213 },{ 106,222,177,78,133,222 },{ 0,2,120,119,255,120 },{ 75,164,11,47,236,164 },{ 198,67,6,9,246,198 },

	{ 207,185,176,9,37,207 },{ 3,12,132,117,248,132 },{ 111,220,167,75,126,220 },{ 0,1,95,97,208,95 },{ 109,224,170,75,130,224 },{ 111,225,170,75,128,225 },{ 99,206,153,75,132,206 },{ 0,8,125,117,254,125 },{ 11,103,245,108,243,245 },



	{ 96,209,160,76,136,209 },{ 207,188,186,9,25,207 },{ 104,217,170,77,131,217 },{ 52,126,4,39,201,126 },{ 75,173,11,48,238,173 },{ 212,196,193,13,22,212 },{ 182,50,1,8,253,182 },{ 94,205,158,77,138,205 },{ 10,101,245,108,244,245 },

	{ 0,1,118,119,255,118 },{ 10,97,245,108,244,245 },{ 197,66,4,9,249,197 },{ 75,163,120,61,111,163 },{ 9,101,248,108,245,248 },{ 213,197,187,11,32,213 },{ 183,48,0,7,254,183 },{ 0,3,116,119,254,116 },{ 11,99,245,108,243,245 },

	{ 71,162,7,47,243,162 },{ 195,65,5,9,248,195 },{ 197,67,5,9,248,197 },{ 2,70,189,89,205,189 },{ 199,66,4,9,249,199 },{ 84,175,13,46,234,175 },{ 195,176,171,6,31,195 },{ 0,6,124,118,254,124 },{ 210,191,184,7,30,210 },

	{ 0,1,118,119,254,118 },{ 12,97,245,109,241,245 },{ 16,102,245,108,237,245 },{ 0,0,93,97,208,93 },{ 0,6,132,118,254,132 },{ 202,69,4,9,249,202 },{ 66,159,3,47,249,159 },{ 97,208,156,75,135,208 },{ 78,171,9,47,241,171 },

	{ 10,93,245,109,244,245 },{ 103,214,168,77,132,214 },{ 109,218,171,77,127,218 },{ 4,72,189,89,203,189 },{ 212,192,189,5,27,212 },{ 213,195,191,6,26,213 },{ 65,154,6,48,244,154 },{ 70,158,7,47,242,158 },{ 210,188,183,6,33,210 },

	{ 100,207,159,76,130,207 },{ 0,4,127,118,254,127 },{ 0,7,131,118,254,131 },{ 144,41,0,6,207,144 },{ 101,218,168,77,136,218 },{ 199,68,5,9,247,199 },{ 197,177,171,7,33,197 },{ 71,161,8,47,241,161 },{ 0,7,130,118,254,130 },



	{ 0,1,122,119,255,122 },{ 1,9,133,118,252,133 },{ 84,175,16,47,231,175 },{ 149,45,0,7,207,149 },{ 79,176,12,47,237,176 },{ 16,105,245,108,238,245 },{ 68,161,4,47,248,161 },{ 10,95,238,108,243,238 },{ 202,65,5,9,248,202 },

	{ 98,209,161,76,135,209 },{ 83,173,18,47,227,173 },{ 84,175,17,47,230,175 },{ 54,127,6,39,198,127 },{ 10,104,248,108,243,248 },{ 0,9,142,118,253,142 },{ 0,1,114,119,255,114 },{ 75,163,13,47,234,163 },{ 213,193,188,5,29,213 },

	{ 201,183,179,8,27,201 },{ 10,98,245,108,244,245 },{ 81,172,17,47,228,172 },{ 0,0,95,97,208,95 },{ 199,65,3,9,250,199 },{ 214,198,195,9,22,214 },{ 184,52,1,8,253,184 },{ 96,208,160,77,136,208 },{ 198,67,6,9,246,198 },

	{ 5,94,245,109,249,245 },{ 208,191,186,7,26,208 },{ 14,104,245,108,240,245 },{ 147,44,0,7,207,147 },{ 0,4,132,118,254,132 },{ 84,177,17,47,229,177 },{ 2,88,245,109,252,245 },{ 199,183,174,10,31,199 },{ 0,7,131,118,254,131 },

	{ 201,185,181,6,26,201 },{ 101,216,169,77,135,216 },{ 3,15,139,117,249,139 },{ 74,163,127,63,112,163 },{ 210,193,191,18,23,210 },{ 103,223,175,78,136,223 },{ 91,203,154,77,140,203 },{ 184,57,2,9,251,184 },{ 197,67,6,9,246,197 },

	{ 98,210,158,76,136,210 },{ 0,8,132,118,254,132 },{ 107,221,170,76,131,221 },{ 156,143,137,7,24,156 },{ 103,223,169,76,137,223 },{ 201,73,7,10,245,201 },{ 2,87,245,109,252,245 },{ 7,94,238,108,247,238 },{ 212,193,184,9,32,212 },



	{ 0,54,245,113,254,245 },
	{ 6,69,245,112,248,245 },
	{ 3,68,245,112,250,245 },
	{ 0,40,189,92,208,189 },
	{ 0,67,248,112,254,248 },
	{ 2,71,245,111,252,245 },
	{ 0,51,245,113,255,245 },
	{ 0,60,238,112,254,238 },
	{ 0,67,245,111,254,245 },


	{ 7, 7, 7,0, 0, 6 },{ 6, 6, 6,0, 0, 5 },{ 5, 5, 5,0, 0, 5 },{ 6, 6, 6,0, 51, 10 },{ 6, 7, 7,0, 0, 8 },
	{ 11, 10, 10,0, 0, 10 },{ 11, 10, 10,0, 0, 9 },{ 9, 9, 9,0, 0, 10 },{ 8, 8, 8,0, 0, 6 },{ 7, 7, 7,0, 0, 6 },
	{ 6, 7, 7,0, 0, 8 },{ 23, 22, 25,0, 0, 20 },{ 24, 23, 23,0, 0, 30 },{ 19, 17, 18,0, 0, 13 },{ 14, 13, 13,0, 39, 13 },
	{ 0,0,0,0,0,0 },{ 0,0,0,0,0,0 },{ 0,0,0,0,0,0 },{ 0,0,0,0,0,0 },{ 0,0,0,0,0,0 },

	{ 6,18,145,117,242,145 },{ 0,14,154,117,254,154 },{ 129,245,186,74,120,245 },
	{ 82,143,10,35,193,143 },{ 4,18,157,117,247,157 },{ 131,245,188,75,118,245 },
	{ 223,195,176,12,53,223 },{ 26,109,238,108,226,238 },{ 29,118,245,107,223,245 },

	{ 40,116,245,108,212,245 },{ 129,245,186,74,120,245 },{ 2,20,162,116,251,162 },
	{ 170,68,0,9,207,170 }	,{ 230,98,1,12,253,230 },{ 1,18,165,116,253,165 },
	{ 92,174,6,44,246,174 },{ 214,81,0,11,254,214 },{ 0,9,150,118,254,150 },

	{ 130,245,184,73,118,245 },{ 114,194,28,44,217,194 },{ 49,127,245,108,203,245 },
	{ 83,141,16,35,184,141 },{ 43,122,248,108,210,248 },{ 245,228,216,12,30,245 },
	{ 95,175,10,44,240,175 },{ 236,204,193,7,46,236 },{ 126,245,183,74,123,245 },

	{ 245,212,199,8,47,245 },{ 47,123,245,108,205,245 },{ 245,224,211,10,35,245 },
	{ 3,10,112,96,200,112 },{ 117,196,26,44,220,196 },{ 245,227,215,12,32,245 },
	{ 92,172,9,44,241,172 },{ 101,177,16,44,232,177 },{ 32,116,245,108,221,245 },

	{ 213,81,0,11,254,213 },{ 31,119,245,107,222,245 },{ 221,95,1,12,252,221 },
	{ 88,184,135,60,108,184 },{ 239,218,202,13,39,239 },{ 0,13,157,117,253,157 },
	{ 194,64,0,9,254,194 },{ 201,75,2,11,251,201 },{ 212,82,1,11,253,212 },

	{ 104,184,13,44,236,184 },{ 228,98,3,12,251,228 },{ 135,245,188,74,114,245 },
	{ 93,184,133,59,102,184 },{ 128,248,183,73,123,248 },{ 245,224,208,12,39,245 },
	{ 0,7,125,118,254,125 },{ 24,107,238,108,228,238 },{ 241,207,192,9,51,241 },


	{ 0,6,113,118,254,113 },{ 0, 11, 129, 117, 254, 129 },
	{ 21, 108, 241, 108, 232, 241 },{ 35, 116, 245, 108, 218, 245 },
	};
	//转为Mat以调用  
	Mat labelmat(162 + 20 + 9 + 54, 1, CV_32SC1, lable);
	Mat trainingmat(245, 6, CV_32FC1, trainingdata);
	//训练的初始化  
	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::C_SVC);
	svm->setKernel(SVM::LINEAR);
	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
	//开始训练  
	svm->train(trainingmat, ROW_SAMPLE, labelmat);
	svm->save("color.xml");
	////测试测试  
	//Mat result;
	////URFDLB WRGYOB 123456 遵循某种玄学
	//float teatData[6][6] = { 
	//	
	//};
	//Mat query(6, 6, CV_32FC1, teatData);
	//svm->predict(query, result);
	//cout << "分类结果为：" << endl;
	//cout << result;
	waitKey(-1);
}


//	for (int x = 0; x < 3; x++) {
//		for (int y = 0; y < 3; y++) {
//			long pixel[6] = { 0 };
//			int temp[6] = { 0 };
//			int count = 0;
//			for (int i = 0; i < 100; i++) {
//				for (int j = 0; j < 100; j++) {
//					//if (srcimage.at<cv::Vec3b>(50 + 200 * x + i, 50 + 200 * y + j)[0]<10 || srcimage.at<cv::Vec3b>(50 + 200 * x + i, 50 + 200 * y + j)[1]<10 || srcimage.at<cv::Vec3b>(50 + 200 * x + i, 50 + 200 * y + j)[2]<10) {
//					//	//(2,1)(1,0) 
//					//	//std::cout << '[' << srcimage.at<cv::Vec3b>(50 + 200 * x + i, 50 + 200 * y + j)[0] << ',' << srcimage.at<cv::Vec3b>(50 + 200 * x + i, 50 + 200 * y + j)[1] << ',' << srcimage.at<cv::Vec3b>(50 + 200 * x + i, 50 + 200 * y + j)[2] << ',';
//					//	count++;
//					//}
//					//else
//					//{
//						for (int k = 0; k < 3; k++)
//						{
//							pixel[k] += srcimage.at<cv::Vec3b>(50 + 200 * x + i, 50 + 200 * y + j)[k];
//							temp[k] = srcimage.at<cv::Vec3b>(50 + 200 * x + i, 50 + 200 * y + j)[k];
//							pixel[k + 3] += hsvimage.at<cv::Vec3b>(50 + 200 * x + i, 50 + 200 * y + j)[k];
//							temp[k + 3] = hsvimage.at<cv::Vec3b>(50 + 200 * x + i, 50 + 200 * y + j)[k];
//							//srcimage.at<cv::Vec3b>(50 + 200 * x + i, 50 + 200 * y + j)[k] = 255;
//						}
//						cout << '[' << temp[0] << ',' << temp[1] << ',' << temp[2] << ',' << temp[3] << ',' << temp[4] << ',' << temp[5] << ']' << ' ';
//					//}
//				}
//			}
//			for (int i = 0; i < 6; i++) {
//				pixel[i] = pixel[i] / (10000 - count);
//			}
//			std::cout << pixel[0] << ' ' << pixel[1] << ' ' << pixel[2] <<' ' <<pixel[3] << ' ' << pixel[4] << ' ' << pixel[5] << endl;
//			//col+=WriteColor(srcimage, pixel, x, y);
//		}
//	}
//	imshow("RGB", srcimage);
//	waitKey(10);
//}
