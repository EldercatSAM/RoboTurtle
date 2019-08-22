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
#define N 15
#define blockSize 51
#define constValue 5
#define Open_size 5
#define Close_size 7
#define firstPlace 3
#define Pi 3.14159
#define ColorParameter 1.6 
#define SearchFactor 0.3

void rgb2bin(Mat& rgb, Mat& bin);
int biasJudge(Mat& bin);
double CapLine();

#endif