#include "/home/pi/RoboTurtle/Turtle/servo/pca9685_wiringpi.h"
#include "/home/pi/RoboTurtle/Turtle/servo/basicfunc.h"


#define rotate_parameter 13.4
//when this parameter is 16.5 
//it act like a dumb donkey, why so?

void Turn_right(int degree){
	#define TR_Steps 8
	int ti[TR_Steps] = {50,250,50,250,50,250,50,250};
	int Moves[TR_Steps][ServoNum] = {
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,1800,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,1500,1500,1000,1500,1500,1200,1500,1500,2000,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500,
		1500,1800,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,1500,1500,1200,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500};
	Moves[5][2]-=rotate_parameter*degree;
	Moves[6][2]-=rotate_parameter*degree;
	Moves[0][5]-=rotate_parameter*degree;
	Moves[7][5]-=rotate_parameter*degree;
	Moves[3][8]-=rotate_parameter*degree;
	Moves[4][8]-=rotate_parameter*degree;
	Moves[1][11]-=rotate_parameter*degree;
	Moves[2][11]-=rotate_parameter*degree;
	//printf("%d\n",Moves[5][2]);

	for (int i=0;i<TR_Steps;i++) {
		action(ti[i],Moves[i]);
		for (int j=0;j<ServoNum;j++)
			servos[j]=Moves[i][j];
	}
	//#endif
}

void Turn_left(int degree) {
	#define TL_Steps 8
	int ti[TL_Steps] = { 50,250,50,250,50,250,50,250 };
	int Moves[TL_Steps][ServoNum] = {
		1500,1800,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,1500,1500,1000,1500,1500,1200,1500,1500,2000,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,1800,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,1500,1500,1200,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500 };
	Moves[1][2] += rotate_parameter * degree;
	Moves[2][2] += rotate_parameter * degree;
	Moves[0][5] += rotate_parameter * degree;
	Moves[7][5] += rotate_parameter * degree;
	Moves[3][8] += rotate_parameter * degree;
	Moves[4][8] += rotate_parameter * degree;
	Moves[5][11] += rotate_parameter * degree;
	Moves[6][11] += rotate_parameter * degree;

	for (int i = 0; i < TL_Steps; i++) {
		action(ti[i], Moves[i]);
		for (int j = 0; j < ServoNum; j++)
			servos[j] = Moves[i][j];
	}
	//#endif
}
/*
gcc main.c -o main -lwiringPi 
./main

*/