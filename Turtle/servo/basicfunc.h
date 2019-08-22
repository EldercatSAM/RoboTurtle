#ifndef BASICFUNC_H
#define BASICFUNC_H

#include <stdio.h>
#include <unistd.h>
#include "/home/pi/RoboTurtle/Turtle/servo/pca9685_wiringpi.h"
#define steptime 10

const int Deviation[ServoNum] = {-120,-130,-50,-40,-40,-45,-80,-100,-30,-20,-30,-90};//舵机误差 
int servos[ServoNum] = {1500,1500,1500,1500,1500,1500,1500,1500,1500,1500,1500,1500};//存储舵机位置，初始化为归中 

void action(int Action_time,const int *Moves);
void adjust();
#endif

