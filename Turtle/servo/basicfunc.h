#pragma once
#ifndef BASICFUNC_H
#define BASICFUNC_H

#include <stdio.h>
#include "/home/pi/RoboTurtle/Turtle/servo/pca9685_wiringpi.h"
#define steptime 10

void sleep(int x){//if this program runs slow, check here.
	for(int i=x*1000;i>0;i--);
}

const int Deviation[ServoNum] = {-12,0,70,50,80,32,12,0,15,90,80,60};//舵机误差 
int servos[ServoNum] = {1500,1500,1500,1500,1500,1500,1500,1500,1500,1500,1500,1500};//存储舵机位置，初始化为归中 

void action(int Action_time,int *Moves){
	/*if(sizeof(Moves)!=ServoNum){
		printf("Parameter Err!\d");
		return ; 
	}*/
	for(int cnt = 0; cnt < Action_time; cnt+=steptime){
		for(int i = 0; i < ServoNum; i++){
			pca9685_setmk(pca9685, i, servos[i]+Deviation[i]+(Moves[i]-servos[i])/Action_time*cnt);
			//公式：初位置+偏差+（末位置-初位置）*当前动作数 
		}
		sleep(steptime);
	}
	for(int i=0; i<ServoNum; i++){//更新末位置 
		servos[i] = Moves[i];
	} 
}

#endif
