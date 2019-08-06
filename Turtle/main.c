#pragma once
#include "/home/pi/RoboTurtle/Turtle/servo/basicfunc.h"
#include "/home/pi/RoboTurtle/Turtle/servo/walk.c"

int main() {
	pca9685 = pca9685_init(0x40);
	
	while (1) {
		/*for (int i = 500; i <= 2500; i++)
			pca9685_setmk(pca9685, 0, i);
		for (int i = 2500; i >= 500; i--)
			pca9685_setmk(pca9685, 0, i);*/
		
		Move_forward();
		}
}

