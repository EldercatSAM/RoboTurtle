#include "/home/pi/RoboTurtle/Turtle/easypr.h"
#include <iostream>
/*
cd RoboTurtle/Turtle
g++ -o easypr easypr.cpp -L. -leasypr

*/
using namespace easypr;

int main(){
	CPlateRecognize pr;
	pr.setResultShow(false);
	pr.setDetectType(PR_DETECT_CMSER);
     
	vector<CPlate> plateVec;
	Mat src = imread("/home/pi/RoboTurtle/EasyPR/resources/image/test.jpg");
	int result = pr.plateRecognize(src, plateVec);
	
	CPlate plate = plateVec.at(1);
	Mat plateMat = plate.getPlateMat();
	RotatedRect rrect = plate.getPlatePos();
	string license = plate.getPlateStr();
	
	std::cout<<license<<std::endl;
	return 0;
}
