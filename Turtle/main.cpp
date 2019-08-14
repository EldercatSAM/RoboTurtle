//#pragma once
#include "/home/pi/RoboTurtle/Turtle/servo/basicfunc.h"
#include "/home/pi/RoboTurtle/Turtle/servo/walk.cpp"
#include "/home/pi/RoboTurtle/Turtle/servo/turn.cpp"
#include "/home/pi/RoboTurtle/Turtle/line/line1.cpp"
#include <stdio.h>

#define interimDegree 15
int main() {
	pca9685 = pca9685_init(0x40);
	int i=9;
	while (i--) {
		/*for (int i = 500; i <= 2500; i++)
			pca9685_setmk(pca9685, 0, i);
		for (int i = 2500; i >= 500; i--)
			pca9685_setmk(pca9685, 0, i);*/
		
		//turn();
		double CurrentAngle = CapLine();
		if (CurrentAngle >= interimDegree)
			turnright(CurrentAngle);
		else if (CurrentAngle <= -interimDegree)
			turnleft(CurrentAngle);
		else
			Move_forward();
		//Turn_1();
		//turnleft(20);
		//Move_forward();
		//printf("%d ",i);
		}
}

/*
g++ main.cpp -o main `pkg-config --cflags --libs opencv` -lwiringPi

*/

