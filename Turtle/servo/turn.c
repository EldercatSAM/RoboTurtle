#include "/home/pi/RoboTurtle/Turtle/servo/pca9685_wiringpi.h"
#include "/home/pi/RoboTurtle/Turtle/servo/basicfunc.h"

void turnleft(){
	#define steps 8
	
	int ti[steps] = {50,250,50,250,50,250,50,250};
	int Moves[steps][ServoNum] = {
		1500,2000,1500,1500,1000,700,1500,1000,1500,1500,1800,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,700,
		1500,2000,1500,1500,1000,1500,1500,1200,1500,1500,2000,700,
		1500,2000,1500,1500,1000,1500,1500,1000,700,1500,2000,1500,
		1500,1800,1500,1500,1000,1500,1500,1000,700,1500,2000,1500,
		1500,2000,700,1500,1000,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,700,1500,1200,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,1500,1500,1000,700,1500,1000,1500,1500,2000,1500};
	
	for (int i=0;i<steps;i++) {
		action(ti[i],Moves[i]);
		for (int j=0;j<ServoNum;j++)
			servos[j]=Moves[i][j];
	}
	//#endif
}
