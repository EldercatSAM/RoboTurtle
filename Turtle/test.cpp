#include "/home/pi/RoboTurtle/Turtle/servo/basicfunc.h"
#include "/home/pi/RoboTurtle/Turtle/servo/walk.c"
#include "/home/pi/RoboTurtle/Turtle/servo/turn.c"

int main() {
	pca9685 = pca9685_init(0x40);
	int i=4;
	while (i--) {
		Move_forward();
		sleep(1);
		}
}
/*
cd RoboTurtle/Turtle
g++ -o test test.cpp -lwiringPi

*/
