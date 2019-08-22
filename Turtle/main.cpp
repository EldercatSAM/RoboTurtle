//#pragma once
#include "/home/pi/RoboTurtle/Turtle/Turtle.h"
#include <stdio.h>

int main() {
	pca9685 = pca9685_init(0x40);
	RoboTurtle Sam;
	while (1) {
		Sam.takeAction();
	}
/*
	int i=9;
	while (1) {
		for (int i = 500; i <= 2500; i++)
			pca9685_setmk(pca9685, 0, i);
		for (int i = 2500; i >= 500; i--)
			pca9685_setmk(pca9685, 0, i);
		
		//turn();
		stay_Middle();
		sleep(0.8);
		double CurrentAngle = CapLine();
		//if (CurrentAngle == -999) break;
		CurrentAngle = int(CurrentAngle);
		//waitKey(0);
		//Move_forward();
		cout<<CurrentAngle<<endl;
		if (CurrentAngle >= interimDegree){
			cout<<"turnright "<<CurrentAngle<<" degrees"<<endl;
			turnright(CurrentAngle);
		}
		else if (CurrentAngle <= -interimDegree){
			cout<<"turnleft "<<CurrentAngle<<" degrees"<<endl;
			turnleft(CurrentAngle);
		}
		else{
			cout<<"Moveforward"<<endl;
			Move_forward();
		}
		//Turn_1();
		//turnleft(20);
		//Move_forward();
		//printf("%d ",i);
		}
*/
}

/*
cd RoboTurtle/Turtle
g++ -o main main.cpp `pkg-config --cflags --libs opencv` -I/usr/local/include -L/usr/local/lib -lwiringPi

*/

