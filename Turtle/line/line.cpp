#include "/home/pi/RoboTurtle/Turtle/line/line.h"

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
	int rowNumber = bin.rows - boarderWidth;// avoid the border
	int colNumber = bin.cols;
	for (int i = 1; i <= biasDistance; i++) {
		if (bin.at<uchar>(rowNumber, colNumber / 2 + i ) == 255 || bin.at<uchar>(rowNumber, colNumber / 2 - i ) == 255)
			return 0;
	}
	for (int i = biasDistance; i <= colNumber; i++) {
		if (bin.at<uchar>(rowNumber, colNumber / 2 + i ) == 255)
			return 1;
		if (bin.at<uchar>(rowNumber, colNumber / 2 - i ) == 255)
			return -1;
	}
	for (int i = biasDistance; i <= colNumber; i++) {
		if (bin.at<uchar>(rowNumber / 2, colNumber / 2 + i ) == 255)
			return 1;
		if (bin.at<uchar>(rowNumber / 2, colNumber / 2 - i ) == 255)
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
	int judge = 0;//sign if the line is at center
	bool onCurve = false;
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
		
	Mat element1 = getStructuringElement(MORPH_RECT, Size(Open_size, Open_size));
	erode(binary, binary, element1);//腐蚀
	dilate(binary, binary, element1);
	Mat element2 = getStructuringElement(MORPH_RECT, Size(Close_size,Close_size));
	dilate(binary, binary, element2);//膨胀
	erode(binary, binary, element2);
	imshow("binary", binary);
	judge = biasJudge(binary);
	Rect rec[N];
	Point2f diff[N];
	//int effectivePoint = 0;
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
	double Degrees[N] = { 0 };
	int k = 0;
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
				x[k] = mc[j].x; y[k] = mc[j].y;
				k++;
				//effectivePoint++;
				//cout << mc[j].x << "," << mc[j].y << endl;
			}
		}
	}
	int cnt = 0, exclude = 0;
	double degrees = 0;
	for (int i = 0; i < k - 1; i++) {
		double currentdegree = atan(-((x[i + 1] - x[i]) / (y[i + 1] - y[i]))) * 180 / Pi;
		Degrees[i] = currentdegree;
		if(i < (k-1)/2)
			degrees += currentdegree / (k-1) *2;
		/*if (cnt == 1 && degrees * currentdegree < 0) { //the first three points lean on different side
			degrees = 0;
			cnt--;
		}
		if(cnt > 1 && degrees * currentdegree < 0) continue;
		degrees += currentdegree;
		cnt++;*/
	}
	cout<< "degrees[0] = "<<Degrees[0]<<endl;
	cout<< "degrees[k-3] = "<<Degrees[k-3]<<endl;
	if ((fabs(Degrees[k - 3])+fabs(Degrees[k-2])) > curveParameter * (fabs(Degrees[0])+fabs(Degrees[1])) && fabs(Degrees[0]) > T_interimDegree) onCurve = true;
	imshow("gray", gray);
	//imshow("binary", binary);
	waitKey(33);
	//waitKey(0);
	if (judge == 1)
		return 199909; //
	else if (judge == -1)
		return 200012;
	else if (judge == 3)
		return 200000;

	if (!onCurve)
		return degrees;
	else
		return Degrees[k-2]  + 300000;
}

