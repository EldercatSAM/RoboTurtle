#include "/home/pi/RoboTurtle/Turtle/servo/pca9685_wiringpi.h"
#include "/home/pi/RoboTurtle/Turtle/servo/basicfunc.h"


//#define ...

void Move_forward(){
	
	#define WalkSteps 9
	//const int Steps = 8;
	int ti[WalkSteps] = {150,50,150,50,150,50,150,50,50};
	int b[WalkSteps][ServoNum] = {
	 1500,2000,1500,1500,1000,1000,1500,1000,1500,1500,2000,1500,
	 1500,2000,1500,1500,1000,1000,1500,1000,1500,1500,1600,1500,
	 1500,2000,1500,1500,1000,1000,1500,1000,1500,1500,2000,2000,
	 1500,2000,1500,1500,1400,1500,1500,1000,1500,1500,2000,2000,
	 1500,2000,2000,1500,1000,1500,1500,1000,1500,1500,2000,1500,
	 1500,2000,2000,1500,1000,1500,1500,1400,1500,1500,2000,1500,
	 1500,2000,2000,1500,1000,1500,1500,1000,1000,1500,2000,1500,
	 1500,1600,1500,1500,1000,1500,1500,1000,1000,1500,2000,1500,
	 1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500};
	for (int i=0;i<WalkSteps;i++){
		action(ti[i],b[i]);//std::cout<<"cylssz"<<std::endl;
	}
		
	//#endif
}
