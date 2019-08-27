#include "/home/pi/RoboTurtle/Turtle/servo/walk.h"

void Move_forward(){
	#define WalkSteps 8
	int ti[WalkSteps] = {150,50,150,50,150,50,150,50};
	int b[WalkSteps][ServoNum] = {
	 1500,2000,1500,1500,1000,1000,1500,1000,1500,1500,2000,1500,
	 1500,2000,1500,1500,1000,1000,1500,1000,1500,1500,1600,1500,
	 1500,2000,1500,1500,1000,1000,1500,1000,1500,1500,2000,2000,
	 1500,2000,1500,1500,1400,1500,1500,1000,1500,1500,2000,2000,
	 1500,2000,2000,1500,1000,1500,1500,1000,1500,1500,2000,1500,
	 1500,2000,2000,1500,1000,1500,1500,1400,1500,1500,2000,1500,
	 1500,2000,2000,1500,1000,1500,1500,1000,1000,1500,2000,1500,
	 1500,1600,1500,1500,1000,1500,1500,1000,1000,1500,2000,1500};
	 //1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500};
	for (int i=0;i<WalkSteps;i++){
		action(ti[i]*0.8,b[i]);
	}
}

void Move_left(int dis){
    #define ML_steps 8
    int ti[ML_steps] = {200,200,200,200,200,200,200,200};
	int b[ML_steps][ServoNum] = {
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,1600,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,1500,1500,1000,1500,1500,1400,1500,1500,2000,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,1500,1500,1400,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500,
		1500,1600,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500};
		
	for(int i=0;i<3;i++)
		b[4+i][2] -= walkCoefficient * dis;
		b[i][8]   += walkCoefficient * dis;
	for(int i=0;i<2;i++){
		b[7-i][5] += walkCoefficient * dis;
		b[2+i][11]-= walkCoefficient * dis;
	}
	
	for (int i=0;i<ML_steps;i++)
		action(ti[i]/200*dis*walkCoefficient,b[i]);
}

void Move_right(int dis){
    #define MR_steps 8
    int ti[MR_steps] = {200,200,200,200,200,200,200,200};
	int b[MR_steps][ServoNum] = {
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,1500,1500,1000,1500,1500,1400,1500,1500,2000,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,1600,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500,
		1500,1600,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,1500,
		1500,2000,1500,1500,1400,1500,1500,1000,1500,1500,2000,1500};
	
	for(int i=0;i<3;i++)
		b[4+i][5] += walkCoefficient * dis;
		b[i][11]  -= walkCoefficient * dis;
	for(int i=0;i<2;i++){
		b[7-i][2] -= walkCoefficient * dis;
		b[2+i][8] += walkCoefficient * dis;
	}
	
	for (int i=0;i<MR_steps;i++)
		action(ti[i]/200*dis*walkCoefficient,b[i]);
}

void Move_backward(){
   // #ifndef MB_steps
    #define MB_steps 8
    int ti[MB_steps] = {50,150,50,150,50,150,50,150};
	int b[MB_steps][ServoNum] = {
		1500,1800,1500,1500,1000,1500,1500,1000,1000,1500,2000,1500,
		1500,2000,2000,1500,1000,1500,1500,1000,1000,1500,2000,1500,
		1500,2000,2000,1500,1000,1500,1500,1200,1000,1500,2000,1500,
		1500,2000,1500,1500,1000,1500,1500,1000,1500,1500,2000,2000,
		1500,2000,1500,1500,1200,1500,1500,1000,1500,1500,2000,2000,
		1500,2000,1500,1500,1000,1000,1500,1000,1500,1500,2000,2000,
		1500,2000,1500,1500,1000,1000,1500,1000,1500,1500,1800,2000,
		1500,2000,1500,1500,1000,1500,1500,1000,1000,1500,2000,1500};
	for (int i=0;i<MB_steps;i++)
		action(ti[i]*0.75,b[i]);
//	#endif
}
