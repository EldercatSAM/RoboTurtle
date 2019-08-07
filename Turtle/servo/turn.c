#pragma once

#include "/home/pi/RoboTurtle/Turtle/servo/pca9685_wiringpi.h"
#include "/home/pi/RoboTurtle/Turtle/servo/basicfunc.h"
/*
void Turn(){
    #ifndef steps
    #define steps 8
    int ti[steps] = {50,250,50,250,50,250,50,250};
    int b[steps][ServoNum] = {
	1500,2000,1500,1500,1000,1100,1500,1000,1500,1500,1800,1500,
	1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1100,
	1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1100,
	1500,2000,1500,1500,1000,1500,1500,1000,1100,1500,2000,1500,
	1500,1800,1500,1500,1000,1500,1500,1000,1100,1500,2000,1500,
	1500,2000,1100,1500,1000,1500,1500,1000,1500,1500,2000,1500,
	1500,2000,1100,1500,1200,1500,1500,1000,1500,1500,2000,1500,
	1500,2000,1500,1500,1000,1100,1500,1000,1500,1500,2000,1500};
    for (int i=0;i<steps;i++)
	action(ti[i],b[i]);
    #endif
}
*/
void Turn(){
	#ifndef steps
	#define steps 8
	int ti[steps] = {150,50,150,50,150,50,150,50};
	int b[steps][ServoNum] = {
	 1500,2000,1500,1500,1000,700,1500,1000,1500,1500,1800,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,700,
		1500,2000,1500,1500,1000,1500,1500,1200,1500,1500,2000,700,
		1500,2000,1500,1500,1000,1500,1500,1000,700,1500,2000,1500,
		1500,1800,1500,1500,1000,1500,1500,1000,700,1500,2000,1500,
		1500,2000,700,1500,1000,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,700,1500,1200,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,1500,1500,1000,700,1500,1000,1500,1500,2000,1500};
	for (int i=0;i<steps;i++)
		action(ti[i],b[i]);
	#endif
}
