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
		//灰度图
		cvtColor(image, gray, CV_BGR2GRAY);
		pyrDown(gray, gray);
		//删除图像中的偶数行和列
		equalizeHist(gray, gray);
		/*2、函数功能
		直方图均衡化，用于提高图像的质量；
		该函数使用以下算法对输入图像的直方图进行均衡化：
			(1) 计算原图像的直方图H；
				直方图是图像中像素强度分布的图形表达方式，它统计了图像中每一个强度值所具有的像素个数。
			(2) 将柱状图归一化，使柱状图bin的总和为255；
				直方图均匀化相当于将直方图进行了拉伸
			(3) 计算直方图的积分;
			(4) 使用H‘作为查找表转换图像：dst(x, y) = H’(src(x, y)；
			该算法对图像的亮度进行了归一化处理，提高了图像的对比度；
		*/
		//高斯滤波 去噪
		GaussianBlur(gray, gray, Size(3, 3), 0, 0);
		/*
		图像卷积滤波：
		分为两个矩阵：原图像矩阵（二维像素矩阵）和卷积核（二维图像滤波矩阵）
		对于原矩阵中的每一个像素，以它作为中心像素，计算它及周边像素与滤波器矩阵对应项的乘积之和，即为新矩阵中对应像素的值
		可以看出，滤波器也是有一定要求的:
		(1） 滤波器的大小应该是奇数，这样它才有一个中心，例如3x3，5x5或者7x7。有中心了，也有了半径的称呼，例如5x5大小的核的半径就是2。
		(2) 滤波器矩阵所有的元素之和应该要等于1，这是为了保证滤波前后图像的亮度保持不变。当然了，这不是硬性要求了。
		(3) 如果滤波器矩阵所有元素之和大于1，那么滤波后的图像就会比原图像更亮，反之，如果小于1，那么得到的图像就会变暗。如果和为0，图像不会变黑，但也会非常暗。
		(4) 对于滤波后的结构，可能会出现负数或者大于255的数值。对这种情况，我们将他们直接截断到0和255之间即可。对于负数，也可以取绝对值。
		卷积核举例：
		空卷积核：
		0 0 0
		0 1 0
		0 0 0  无事发生
		图像锐化边缘：
		-1 -1 -1
		-1  9 -1
		-1 -1 -1 中间额外+1，使图像保持相同的亮度。
		加大滤波器会有更为精细的锐化效果
		-1 -1 -1 -1 -1
		-1  2  2  2 -1
		-1  2  8  2 -1
		-1  2  2  2 -1
		-1 -1 -1 -1 -1
		均值模糊
		 0  0.2  0
		0.2 0.2 0.2
		 0  0.2  0
		由于没有将和中央点的距离加权，模糊的效果一般
		正态分布和高斯函数：
		使用正态分布，中心点为零点作为权重分配模式显然可取
		图像为二维，故选用二阶正态分布，正态分布的密度函数为高斯函数：
		G(x,y) = 1/(2πσ^2)exp-(x^2+y^2)/2σ^2
		方法：设一周点坐标为:
		(-1,1) (0,1) (1,1)
		(-1,0) (0,0) (1,0)
		(-1,-1)(0,-1)(1,-1)
		带入函数求得权重矩阵，再分别将权重矩阵中每一个元素除以权重矩阵元素之和(归一化)，就得到了权重矩阵
		拿权重矩阵分别与每个点相乘，然后相加，就得到了中心点高斯模糊的值
		*/
		adaptiveThreshold(gray, binary, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, blockSize, constValue);
		/*
		二值化
		参数说明
		参数1：输入图像
		参数2：输出图像（与输入图像同样的尺寸和类型）
		参数3：预设满足条件的最大值
		参数4：指定自适应阈值算法。可选择ADAPTIVE_THRESH_MEAN_C 或 ADAPTIVE_THRESH_GAUSSIAN_C两种。（具体见下面的解释）。
		参数5：指定阈值类型。可选择THRESH_BINARY或者THRESH_BINARY_INV两种。（即二进制阈值或反二进制阈值）。
		参数6：表示邻域块大小，用来计算区域阈值，一般选择为3、5、7......等。
		参数7：参数C表示与算法有关的参数，它是一个从均值或加权均值提取的常数，可以是负数。（具体见下面的解释）。
		-------------------------------------------------------------------------
		对参数4与参数7内容的解释：
		自适应阈值化计算大概过程是为每一个象素点单独计算的阈值，即每个像素点的阈值都是不同的，就是将该像素点周围B*B区域内的像素加权平均，然后减去一个常数C，从而得到该点的阈值。B由参数6指定，常数C由参数7指定。
		参数4中：
		ADAPTIVE_THRESH_MEAN_C，为局部邻域块的平均值。该算法是先求出块中的均值，再减去常数C。
		ADAPTIVE_THRESH_GAUSSIAN_C ，为局部邻域块的高斯加权和。该算法是在区域中（x，y）周围的像素根据高斯函数按照他们离中心点的距离进行加权计算， 再减去常数C。
		*/
		Mat element_erode = getStructuringElement(MORPH_RECT, Size(maskSize, maskSize));
		erode(binary, binary, element_erode);//腐蚀
		Mat element_dilate = getStructuringElement(MORPH_RECT, Size(maskSize, maskSize));
		dilate(binary, binary, element_dilate);//膨胀
		/*
		腐蚀和膨胀是两种基本的形态学操作，所谓形态学操作，就是改变物体的形状，腐蚀是变瘦，膨胀是变胖，一般针对于二值化图像
		模板：
		1 1 1
		1 1 1
		1 1 1
		膨胀：
		0 0 0 0 0
		0 0 1 1 0
		0 1 1 1 0
		0 0 0 0 0
		0 0 0 0 0
		结果：
		0 1 1 1 1
		1 1 1 1 1
		1 1 1 1 1
		1 1 1 1 1
		0 0 0 0 0
		将每一个元素1扩展为模板 ones(3,3)
		
		腐蚀：
		0 0 1 0 0
		0 1 1 1 1
		0 1 1 1 1
		0 1 1 1 1
		0 0 0 0 0
		结果：
		0 0 0 0 0
		0 0 0 0 0
		0 0 1 1 0
		0 0 0 0 0
		0 0 0 0 0
		每一个满足模板的3x3，都缩成中心的一个点
		腐蚀和膨胀都可以可以平滑对象边缘

		开运算：先腐蚀后膨胀
		作用：分离物体，消除小区域（先腐蚀会消除主要物体外的小区域）
		闭运算：先膨胀后腐蚀
		作用：消除物体内的小黑洞

		其它形态学操作：
		形态学梯度：
		腐蚀图减去膨胀图，得到物体的轮廓

		getStructuringElement函数：获取常用结构元素的形状
		第一个参数 MORPH_RECT， MORPH_ELLIPSE， MORPH_CROSS 分别生成矩形、椭圆和十字形
		第二个参数 获得Mat的大小。
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
		//将图像分成N个横条，横条的高度为ROI_WIDTH，宽度为原宽

		for (int i = 0; i < N; i++){
			ROI[i] = binary(rec[i]);
			vector<vector<Point> > contours;//contours的类型是双重的vector
			vector<Vec4i> hierarchy;//Vec4i是指每一个vector元素中有四个int型数据，这个暂时没有用

			findContours(ROI[i].clone(), contours, hierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
			/*
			contours - 检测到的轮廓，列表list形式，list 中每个元素都是图像中的一个轮廓，这里的每一个元素仍为（点）向量。

			hierarchy -  它和轮廓 contours 个数相同（可选结果），这是一个 ndarray，其中元素个数和轮廓个数相同。每个轮廓 contours[i] 对应 4 个 hierarchy 元素 hierarchy[i][0] ~ hierarchy[i][3]，分别表示后一个轮廓、前一个轮廓、父轮廓、内嵌轮廓的索引编号，如果没有对应项，则该值为负数。（各个轮廓的继承关系。hierarchy也是一个向量，长度和contours相等，每个元素和contours的元素对应。hierarchy的每个元素是一个包含四个整型数的向量）
			
			mode -  轮廓检索模式
			CV.RETR_EXTERNAL - 仅检索外轮廓。并为所有轮廓设置层级结构，如 sets hierarchy[i][2]=hierarchy[i][3]=-1
			CV.RETR_LIST - 检索轮廓但不建立任何层次关系。
			CV.RETR_CCOMP - 检索所有轮廓并将它们组织成两级层次结构。上面的一层为外边界，里面的一层为内孔的边界信息。如果内孔内还有一个连通物体，这个物体的边界也在顶层。
			CV.RETR_TREE - 检索所有轮廓并建立等级树结构的轮廓

			method - 轮廓近似方法
			CV.CHAIN_APPROX_NONE - 存储所有的轮廓点，相邻的两个点的像素位置差不超过1，即max（abs（x1-x2），abs（y2-y1））==1
			CV.CHAIN_APPROX_SIMPLE - 压缩水平、垂直、对角线方向的元素，仅留该方向的终点坐标，例如一个矩形轮廓只需4个点来保存轮廓信息
			CV.CHAIN_APPROX_TC89_L1，CV_CHAIN_APPROX_TC89_KCOS - 使用teh-Chinl 链式近似算法
			该函数会修改输入的图像，故建议使用原始图像的副本，所以在代码中常用 img.copy() 来作为输入图像
			*/
			vector<Moments> mu(contours.size());//用于计算矩
			vector<Point2f> mc(contours.size());

			for (int j = 0; j < contours.size(); j++){
				mu[j] = moments(contours[j], false);//矩
				mc[j] = Point2f(mu[j].m10 / mu[j].m00, mu[j].m01 / mu[j].m00) + diff[i];//“质心”
				/*
				假定每个像素的“质量”与他的像素值相同
				与物理上计算质心的方法相同
				mij = I(x,y) * (x^i) * (y^j)
				m00--> 所有质量之和
				m10--> 质量与横坐标乘积之和
				m11--> 质量与纵坐标乘积之和
				*/
				//cout << mu[j].m10 << " " << mu[j].m01 << " " << mu[j].m00 << endl;
				Scalar color = Scalar(255);  //任意颜色
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
