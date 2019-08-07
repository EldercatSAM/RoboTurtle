#pragma once
#include "/home/pi/RoboTurtle/Turtle/servo/basicfunc.h"

int main(){
	pca9685 = pca9685_init(0x40);
	for(int i=0;i<ServoNum;i++)pca9685_setmk(pca9685,i,1500+Deviation[i]);
//	adjust();
	return 0;
}

