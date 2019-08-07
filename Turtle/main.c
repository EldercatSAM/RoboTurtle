//#pragma once
#include "/home/pi/RoboTurtle/Turtle/servo/basicfunc.h"
#include "/home/pi/RoboTurtle/Turtle/servo/walk.c"
#include "/home/pi/RoboTurtle/Turtle/servo/turn.c"

#include <stdio.h>
int main() {
	pca9685 = pca9685_init(0x40);
	int i=3;
	while (i--) {
		/*for (int i = 500; i <= 2500; i++)
			pca9685_setmk(pca9685, 0, i);
		for (int i = 2500; i >= 500; i--)
			pca9685_setmk(pca9685, 0, i);*/
		
		//turn();
		
		//Turn_1();
		turnleft();
		Move_forward();
		//printf("%d ",i);
		}
}

