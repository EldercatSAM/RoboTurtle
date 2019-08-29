#ifndef BASICFUNC_H
#define BASICFUNC_H

#include <stdio.h>
#include <unistd.h>
#include "/home/pi/RoboTurtle/Turtle/servo/pca9685_wiringpi.h"
#define steptime 15

const int Deviation[ServoNum] = {-100,-75,-50,-40,-40,-45,-90,-100,-30,-50,-50,-90};//舵机误差 
int servos[ServoNum] = {1500,1500,1500,1500,1500,1500,1500,1500,1500,1500,1500,1500};//存储舵机位置，初始化为归中 

void action(int Action_time,const int *Moves){
	/*if(sizeof(Moves)!=ServoNum){
		printf("Parameter Err!\d");
		return ; 
	}*/
	for(int cnt = 0; cnt < Action_time; cnt+=steptime){
		for(int i = 0; i < ServoNum; i++){
			pca9685_setmk(pca9685, i, servos[i]+Deviation[i]+(Moves[i]-servos[i])*cnt/Action_time);
			//公式：初位置+偏差+（末位置-初位置）*当前动作数 
		}
		usleep(steptime);
	}
	for(int i=0; i<ServoNum; i++){//更新末位置 
		servos[i] = Moves[i];
	} 
}

void adjust(){
	int x[12]={1500,1500,1500,1500,1500,1500,1500,1500,1500,1500,1500,1500};
	int ti = 100;
	action(ti,x);
	for(int i=0; i<ServoNum; i++){//更新末位置 
		servos[i] = x[i];
	}
}

void stay_Middle(){
	int x[12]={1000,2000,1500,2000,1000,1500,2000,1000,1500,1000,2000,1500};
	int ti = 100;
	action(ti,x);
	for(int i=0; i<ServoNum; i++){//更新末位置 
		servos[i] = x[i];
	}
}

void stay_Middle_stage(){
	int x[12]={1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500};
	int ti = 100;
	action(ti,x);
	for(int i=0; i<ServoNum; i++){//更新末位置 
		servos[i] = x[i];
	}
}

void stay_High(){
	int x[12] = {1500,2500,2000,1500,500,1300,1500,500,500,1500,2500,2500};
	int ti = 50;
	action(ti,x);
	for(int i=0; i<ServoNum; i++){//更新末位置 
		servos[i] = x[i];
	}
}

void stay_HIGH(){
	int x[12] = {1500,2500,1500,1500,500,1500,1500,500,1500,1500,2500,1500};
	int ti = 50;
	action(ti,x);
	for(int i=0; i<ServoNum; i++){//更新末位置 
		servos[i] = x[i];
	}
}
#endif

