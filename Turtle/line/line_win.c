#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include<vector>
#include<iostream>

using namespace std;
using namespace cv;

#define ROI_WIDTH 10
#define N 20
#define blockSize 51
#define constValue 5
#define maskSize 20
int main(){
	VideoCapture cap(0);
	if (!cap.isOpened()){
		cout << "Camera problem" << endl;
		return -1;
	}

	Mat image,gray,binary,blur_image;
	Mat ROI[N];

	bool stop = false;
	while (!stop){
		cap >> image;
		//�Ҷ�ͼ
		cvtColor(image, gray, CV_BGR2GRAY);
		pyrDown(gray, gray);
		//ɾ��ͼ���е�ż���к���
		equalizeHist(gray, gray);
		/*2����������
		ֱ��ͼ���⻯���������ͼ���������
		�ú���ʹ�������㷨������ͼ���ֱ��ͼ���о��⻯��
			(1) ����ԭͼ���ֱ��ͼH��
				ֱ��ͼ��ͼ��������ǿ�ȷֲ���ͼ�α�﷽ʽ����ͳ����ͼ����ÿһ��ǿ��ֵ�����е����ظ�����
			(2) ����״ͼ��һ����ʹ��״ͼbin���ܺ�Ϊ255��
				ֱ��ͼ���Ȼ��൱�ڽ�ֱ��ͼ����������
			(3) ����ֱ��ͼ�Ļ���;
			(4) ʹ��H����Ϊ���ұ�ת��ͼ��dst(x, y) = H��(src(x, y)��
			���㷨��ͼ������Ƚ����˹�һ�����������ͼ��ĶԱȶȣ�
		*/
		//��˹�˲� ȥ��
		GaussianBlur(gray, gray, Size(3, 3), 0, 0);
		/*
		ͼ�����˲���
		��Ϊ��������ԭͼ����󣨶�ά���ؾ��󣩺;���ˣ���άͼ���˲�����
		����ԭ�����е�ÿһ�����أ�������Ϊ�������أ����������ܱ��������˲��������Ӧ��ĳ˻�֮�ͣ���Ϊ�¾����ж�Ӧ���ص�ֵ
		���Կ������˲���Ҳ����һ��Ҫ���:
		(1�� �˲����Ĵ�СӦ��������������������һ�����ģ�����3x3��5x5����7x7���������ˣ�Ҳ���˰뾶�ĳƺ�������5x5��С�ĺ˵İ뾶����2��
		(2) �˲����������е�Ԫ��֮��Ӧ��Ҫ����1������Ϊ�˱�֤�˲�ǰ��ͼ������ȱ��ֲ��䡣��Ȼ�ˣ��ⲻ��Ӳ��Ҫ���ˡ�
		(3) ����˲�����������Ԫ��֮�ʹ���1����ô�˲����ͼ��ͻ��ԭͼ���������֮�����С��1����ô�õ���ͼ��ͻ�䰵�������Ϊ0��ͼ�񲻻��ڣ���Ҳ��ǳ�����
		(4) �����˲���Ľṹ�����ܻ���ָ������ߴ���255����ֵ����������������ǽ�����ֱ�ӽضϵ�0��255֮�伴�ɡ����ڸ�����Ҳ����ȡ����ֵ��
		����˾�����
		�վ���ˣ�
		0 0 0
		0 1 0
		0 0 0  ���·���
		ͼ���񻯱�Ե��
		-1 -1 -1
		-1  9 -1
		-1 -1 -1 �м����+1��ʹͼ�񱣳���ͬ�����ȡ�
		�Ӵ��˲������и�Ϊ��ϸ����Ч��
		-1 -1 -1 -1 -1
		-1  2  2  2 -1
		-1  2  8  2 -1
		-1  2  2  2 -1
		-1 -1 -1 -1 -1
		��ֵģ��
		 0  0.2  0
		0.2 0.2 0.2
		 0  0.2  0
		����û�н��������ľ����Ȩ��ģ����Ч��һ��
		��̬�ֲ��͸�˹������
		ʹ����̬�ֲ������ĵ�Ϊ�����ΪȨ�ط���ģʽ��Ȼ��ȡ
		ͼ��Ϊ��ά����ѡ�ö�����̬�ֲ�����̬�ֲ����ܶȺ���Ϊ��˹������
		G(x,y) = 1/(2�Ц�^2)exp-(x^2+y^2)/2��^2
		��������һ�ܵ�����Ϊ:
		(-1,1) (0,1) (1,1)
		(-1,0) (0,0) (1,0)
		(-1,-1)(0,-1)(1,-1)
		���뺯�����Ȩ�ؾ����ٷֱ�Ȩ�ؾ�����ÿһ��Ԫ�س���Ȩ�ؾ���Ԫ��֮��(��һ��)���͵õ���Ȩ�ؾ���
		��Ȩ�ؾ���ֱ���ÿ������ˣ�Ȼ����ӣ��͵õ������ĵ��˹ģ����ֵ
		*/
		adaptiveThreshold(gray, binary, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, blockSize, constValue);
		/*
		��ֵ��
		����˵��
		����1������ͼ��
		����2�����ͼ��������ͼ��ͬ���ĳߴ�����ͣ�
		����3��Ԥ���������������ֵ
		����4��ָ������Ӧ��ֵ�㷨����ѡ��ADAPTIVE_THRESH_MEAN_C �� ADAPTIVE_THRESH_GAUSSIAN_C���֡������������Ľ��ͣ���
		����5��ָ����ֵ���͡���ѡ��THRESH_BINARY����THRESH_BINARY_INV���֡�������������ֵ�򷴶�������ֵ����
		����6����ʾ������С����������������ֵ��һ��ѡ��Ϊ3��5��7......�ȡ�
		����7������C��ʾ���㷨�йصĲ���������һ���Ӿ�ֵ���Ȩ��ֵ��ȡ�ĳ����������Ǹ����������������Ľ��ͣ���
		-------------------------------------------------------------------------
		�Բ���4�����7���ݵĽ��ͣ�
		����Ӧ��ֵ�������Ź�����Ϊÿһ�����ص㵥���������ֵ����ÿ�����ص����ֵ���ǲ�ͬ�ģ����ǽ������ص���ΧB*B�����ڵ����ؼ�Ȩƽ����Ȼ���ȥһ������C���Ӷ��õ��õ����ֵ��B�ɲ���6ָ��������C�ɲ���7ָ����
		����4�У�
		ADAPTIVE_THRESH_MEAN_C��Ϊ�ֲ�������ƽ��ֵ�����㷨����������еľ�ֵ���ټ�ȥ����C��
		ADAPTIVE_THRESH_GAUSSIAN_C ��Ϊ�ֲ������ĸ�˹��Ȩ�͡����㷨���������У�x��y����Χ�����ظ��ݸ�˹�����������������ĵ�ľ�����м�Ȩ���㣬 �ټ�ȥ����C��
		*/
		Mat element_erode = getStructuringElement(MORPH_RECT, Size(maskSize, maskSize));
		erode(binary, binary, element_erode);//��ʴ
		Mat element_dilate = getStructuringElement(MORPH_RECT, Size(maskSize, maskSize));
		dilate(binary, binary, element_dilate);//����
		/*
		��ʴ�����������ֻ�������̬ѧ��������ν��̬ѧ���������Ǹı��������״����ʴ�Ǳ��ݣ������Ǳ��֣�һ������ڶ�ֵ��ͼ��
		ģ�壺
		1 1 1
		1 1 1
		1 1 1
		���ͣ�
		0 0 0 0 0
		0 0 1 1 0
		0 1 1 1 0
		0 0 0 0 0
		0 0 0 0 0
		�����
		0 1 1 1 1
		1 1 1 1 1
		1 1 1 1 1
		1 1 1 1 1
		0 0 0 0 0
		��ÿһ��Ԫ��1��չΪģ�� ones(3,3)
		
		��ʴ��
		0 0 1 0 0
		0 1 1 1 1
		0 1 1 1 1
		0 1 1 1 1
		0 0 0 0 0
		�����
		0 0 0 0 0
		0 0 0 0 0
		0 0 1 1 0
		0 0 0 0 0
		0 0 0 0 0
		ÿһ������ģ���3x3�����������ĵ�һ����
		��ʴ�����Ͷ����Կ���ƽ�������Ե

		�����㣺�ȸ�ʴ������
		���ã��������壬����С�����ȸ�ʴ��������Ҫ�������С����
		�����㣺�����ͺ�ʴ
		���ã����������ڵ�С�ڶ�

		������̬ѧ������
		��̬ѧ�ݶȣ�
		��ʴͼ��ȥ����ͼ���õ����������

		getStructuringElement��������ȡ���ýṹԪ�ص���״
		��һ������ MORPH_RECT�� MORPH_ELLIPSE�� MORPH_CROSS �ֱ����ɾ��Ρ���Բ��ʮ����
		�ڶ������� ���Mat�Ĵ�С��
		*/
		Rect rec[N];
		Point2f diff[N];
		for (int i = 0; i < N; i++){
			if (i == N - 1){
				rec[i] = Rect(0, 0, binary.cols, ROI_WIDTH);
				diff[i].x = 0;
				diff[i].y = 0;
			}
			else if (i == 0){
				rec[i] = Rect(0, binary.rows - ROI_WIDTH, binary.cols, ROI_WIDTH);
				diff[i].x = 0;
				diff[i].y = binary.rows - ROI_WIDTH;
			}
			else{
				rec[i] = Rect(0, binary.rows / (N - 1)*(N - 1 - i) - ROI_WIDTH / 2, binary.cols, ROI_WIDTH);
				diff[i].x = 0;
				diff[i].y = binary.rows / (N - 1)*(N - 1 - i) - ROI_WIDTH / 2;
			}
		}
		//��ͼ��ֳ�N�������������ĸ߶�ΪROI_WIDTH�����Ϊԭ��

		for (int i = 0; i < N; i++){
			ROI[i] = binary(rec[i]);
			vector<vector<Point> > contours;//contours��������˫�ص�vector
			vector<Vec4i> hierarchy;//Vec4i��ָÿһ��vectorԪ�������ĸ�int�����ݣ������ʱû����

			findContours(ROI[i].clone(), contours, hierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
			/*
			contours - ��⵽���������б�list��ʽ��list ��ÿ��Ԫ�ض���ͼ���е�һ�������������ÿһ��Ԫ����Ϊ���㣩������

			hierarchy -  �������� contours ������ͬ����ѡ�����������һ�� ndarray������Ԫ�ظ���������������ͬ��ÿ������ contours[i] ��Ӧ 4 �� hierarchy Ԫ�� hierarchy[i][0] ~ hierarchy[i][3]���ֱ��ʾ��һ��������ǰһ������������������Ƕ������������ţ����û�ж�Ӧ����ֵΪ�����������������ļ̳й�ϵ��hierarchyҲ��һ�����������Ⱥ�contours��ȣ�ÿ��Ԫ�غ�contours��Ԫ�ض�Ӧ��hierarchy��ÿ��Ԫ����һ�������ĸ���������������
			
			mode -  ��������ģʽ
			CV.RETR_EXTERNAL - ����������������Ϊ�����������ò㼶�ṹ���� sets hierarchy[i][2]=hierarchy[i][3]=-1
			CV.RETR_LIST - �����������������κβ�ι�ϵ��
			CV.RETR_CCOMP - ����������������������֯��������νṹ�������һ��Ϊ��߽磬�����һ��Ϊ�ڿ׵ı߽���Ϣ������ڿ��ڻ���һ����ͨ���壬�������ı߽�Ҳ�ڶ��㡣
			CV.RETR_TREE - �������������������ȼ����ṹ������

			method - �������Ʒ���
			CV.CHAIN_APPROX_NONE - �洢���е������㣬���ڵ������������λ�ò����1����max��abs��x1-x2����abs��y2-y1����==1
			CV.CHAIN_APPROX_SIMPLE - ѹ��ˮƽ����ֱ���Խ��߷����Ԫ�أ������÷�����յ����꣬����һ����������ֻ��4����������������Ϣ
			CV.CHAIN_APPROX_TC89_L1��CV_CHAIN_APPROX_TC89_KCOS - ʹ��teh-Chinl ��ʽ�����㷨
			�ú������޸������ͼ�񣬹ʽ���ʹ��ԭʼͼ��ĸ����������ڴ����г��� img.copy() ����Ϊ����ͼ��
			*/
			vector<Moments> mu(contours.size());//���ڼ����
			vector<Point2f> mc(contours.size());

			for (int j = 0; j < contours.size(); j++){
				mu[j] = moments(contours[j], false);//��
				mc[j] = Point2f(mu[j].m10 / mu[j].m00, mu[j].m01 / mu[j].m00) + diff[i];//�����ġ�
				/*
				�ٶ�ÿ�����صġ�����������������ֵ��ͬ
				�������ϼ������ĵķ�����ͬ
				mij = I(x,y) * (x^i) * (y^j)
				m00--> ��������֮��
				m10--> �����������˻�֮��
				m11--> ������������˻�֮��
				*/
				//cout << mu[j].m10 << " " << mu[j].m01 << " " << mu[j].m00 << endl;
				Scalar color = Scalar(255);  //������ɫ
				if (contours.size() == 1){
					circle(gray, mc[j], 4, color, -1, 8, 0);
					cout << mc[j].x << "," << mc[j].y << endl;
				}
			}
		}
		cout << endl;
		imshow("gray", gray);
		imshow("binary", binary);
		waitKey(33);
	}
	return 0;
}
