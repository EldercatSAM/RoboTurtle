#include "/home/pi/RoboTurtle/Turtle/Turtle.h"
/*
cd RoboTurtle/Turtle
g++ -o test test.cpp `pkg-config --cflags --libs opencv` -I/usr/local/include -L/usr/local/lib -lwiringPi

cd RoboTurtle/Turtle
./test


*/
int main(){
	pca9685 = pca9685_init(0x40);int i=3;
	//while(1){
	//i=2;
	stay_Middle();
	while(i--)
		Move_forward();
	stay_Middle();
	//waitKey(0);

	return 0;
}

