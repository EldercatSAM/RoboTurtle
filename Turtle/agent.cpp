#include "/home/pi/RoboTurtle/Turtle/Turtle_Agent.h"

/*
cd RoboTurtle/Turtle
g++ -o main main.cpp `pkg-config --cflags --libs opencv` -I/usr/local/include -L/usr/local/lib -lwiringPi

*/
int main() {
	pca9685 = pca9685_init(0x40);
	RoboTurtle Sam;
	while (1) {
		Sam.takeAction();
	}
}
