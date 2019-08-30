#ifndef LINE_H
#define LINE_H

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
#define N 16 //Number of points
#define blockSize 51 //Parameter for adaptivethreshold
#define constValue 5 //Parameter for adaptivethreshold
#define Open_size 12 // Rect size of open operate
#define Close_size 8 // Rect size of close operate
#define Pi 3.14159
#define ColorParameter 1.0 // Threshold for RED
#define biasDistance 120 //Consider how long as off-center
#define SearchFactor 0.4 //Range of line-searching
#define boarderWidth 20 //Search the line from coordination above this value
#define interimDegree 18 //The threshold value to turn when walking on line 
#define T_interimDegree 20 //The threshold value to turn when walking on curve 
#define curveParameter 2.1 // If the last degree is bigger then the first one times this parameter, I judge the robot is on curve

struct Data{
	double distance = 0;
	double degrees = 0;
};

void rgb2bin(Mat& rgb, Mat& bin);
int biasJudge(Mat& bin);
Data CapLine();



#endif
