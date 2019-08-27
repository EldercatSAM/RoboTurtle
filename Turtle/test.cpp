#include "/home/pi/RoboTurtle/Turtle/Turtle_Agent.h"

/*
cd RoboTurtle/Turtle
g++ -o test test.cpp `pkg-config --cflags --libs opencv` -I/usr/local/include -L/usr/local/lib -lwiringPi

cd RoboTurtle/Turtle
./test

*/
int main(){
	pca9685 = pca9685_init(0x40);
	Up_platform();

	return 0;
}

