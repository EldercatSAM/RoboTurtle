#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include<vector>
#include<math.h>

using namespace std;
using namespace cv;

#define ROI_WIDTH 10
#define N 15
#define blockSize 51
#define constValue 5
#define Open_size 5
#define Close_size 7
#define firstPlace 3
#define Pi 3.14159
#define ColorParameter 1.6 
#define SearchFactor 0.3

void rgb2bin(Mat& rgb, Mat& bin) {
	cvtColor(rgb, bin, CV_BGR2GRAY);
	int rowNumber = rgb.rows;
	int colNumber = rgb.cols;
	
	for (int i = 0; i < rowNumber; i++)//��
	{
		for (int j = 0; j < colNumber; j++)//��
		{
			if (rgb.at<Vec3b>(i, j)[2] * ColorParameter > (rgb.at<Vec3b>(i, j)[0] + rgb.at<Vec3b>(i, j)[1]))
				bin.at<uchar>(i, j) = 255;//Red
			else
				bin.at<uchar>(i, j) = 0;
		}
	}
}

int biasJudge(Mat& bin) {
	int rowNumber = bin.rows - 5;// avoid the border
	int colNumber = bin.cols;
	for (int i = 1; i <= 5; i++) {
		if (bin.at<uchar>(rowNumber, colNUmber / 2 + i) == 255 || bin.at<uchar>(rowNumber, colNUmber / 2 - i) == 255)
			return 0;
	}
	for (int i = 5; i <= colNumber * SearchFactor; i++) {
		if (bin.at<uchar>(rowNumber, colNUmber / 2 + i) == 255)
			return 1;
		if (bin.at<uchar>(rowNumber, colNUmber / 2 - i) == 255)
			return -1;
	}
	return 3;//Can't find a red line in the field
}

double CapLine() {
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cout << "Camera problem" << endl;
		return -999;
	}

	Mat image, gray, binary, blur_image;
	Mat ROI[N];

	int step = 1;
	double degrees;
	while (step--) {
		cap >> image;
		cvtColor(image, gray, CV_BGR2GRAY);
		/*//灰度�?
		pyrDown(gray, gray);
		//删除图像中的偶数行和�?
		equalizeHist(gray, gray);
		//直方图均衡化
		GaussianBlur(gray, gray, Size(3, 3), 0, 0);
		//高斯滤波 去噪
		adaptiveThreshold(gray, binary, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, blockSize, constValue);
		//二值化*/
		rgb2bin(image, binary);
		int judge = biasJudge(binary);
		if (judge == 1)
			return 199909; //
		else if (judge == -1)
			return 200012;
		else if (judge == 3)
			return 200000;
		Mat element1 = getStructuringElement(MORPH_RECT, Size(Open_size, Open_size));
		erode(binary, binary, element1);//腐蚀
		dilate(binary, binary, element1);
		Mat element2 = getStructuringElement(MORPH_RECT, Size(Close_size,Close_size));
		dilate(binary, binary, element2);//膨胀
		erode(binary, binary, element2);
		
		Rect rec[N];
		Point2f diff[N];
		int effectivePoint = 0;
		for (int i = 0; i < N; i++) {
			if (i == N - 1) {
				rec[i] = Rect(0, 0, binary.cols, ROI_WIDTH);
				diff[i].x = 0;
				diff[i].y = 0;
			}
			else if (i == 0) {
				rec[i] = Rect(0, binary.rows - ROI_WIDTH, binary.cols, ROI_WIDTH);
				diff[i].x = 0;
				diff[i].y = binary.rows - ROI_WIDTH;
			}
			else {
				rec[i] = Rect(0, binary.rows / (N - 1)*(N - 1 - i) - ROI_WIDTH / 2, binary.cols, ROI_WIDTH);
				diff[i].x = 0;
				diff[i].y = binary.rows / (N - 1)*(N - 1 - i) - ROI_WIDTH / 2;
			}
		}
		//将图像分成N个横条，横条的高度为ROI_WIDTH，宽度为原宽
		double x[N] = { 0 }, y[N] = { 0 };
		for (int i = 0; i < N; i++) {
			ROI[i] = binary(rec[i]);
			vector<vector<Point> > contours;
			vector<Vec4i> hierarchy;

			findContours(ROI[i].clone(), contours, hierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
			//检测轮�?
			vector<Moments> mu(contours.size());//用于计算�?
			vector<Point2f> mc(contours.size());

			for (int j = 0; j < contours.size(); j++) {
				//cout << "contours" << contours.size() << endl;
				mu[j] = moments(contours[j], false);//�?
				mc[j] = Point2f(mu[j].m10 / mu[j].m00, mu[j].m01 / mu[j].m00) + diff[i];
				//计算质心
				Scalar color = Scalar(255);  //任意颜色
				if (contours.size() == 1) {
					circle(gray, mc[j], 4, color, -1, 8, 0);
					x[i] = mc[j].x; y[i] = mc[j].y;
					effectivePoint++;
					//cout << mc[j].x << "," << mc[j].y << endl;
				}
			}
		}
		degrees = 0;
		int cnt = 0, exclude = 0;
		for (int i = 0; i < firstPlace || cnt < effectivePoint / 3; i++) {
			if (x[i] != 0) {
				double currentdegree = atan(-((x[i + 1] - x[i]) / (y[i + 1] - y[i]))) * 180 / Pi;
				if (cnt == 1 && degrees * currentdegree < 0) {
					degrees = 0;
					cnt--;
				}
				if(cnt > 1 && degrees * currentdegree < 0) continue;
				degrees += currentdegree;
				cnt++;
			}
		}
		if (cnt)degrees /= cnt;
		//imshow("img", image);
		imshow("gray", gray);
		//imshow("binary", binary);
		waitKey(33);
	}
	return degrees;
}

