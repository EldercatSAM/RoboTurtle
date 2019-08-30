#pragma once
#ifndef TURTLE_AGENT_H
#define TURTLE_AGENT_H

#include "/home/pi/RoboTurtle/Turtle/servo/walk.c"
#include "/home/pi/RoboTurtle/Turtle/servo/turn.c"
#include "/home/pi/RoboTurtle/Turtle/servo/cross_country.c"
#include "/home/pi/RoboTurtle/Turtle/line/line.cpp"
#include "/home/pi/RoboTurtle/Turtle/ultrasonic/ultrasonic.c"

#define sleeptime 0.3
#define turnTimes 2
#define turnCoefficient 0.8
#define UpDistance 45
#define initialSteps 4
#define StairDistance 1500
#define StairSteps 21
#define PlatformSteps 8
typedef enum {
	INITIALIZE,STAY, MOVE_FORWARD, MOVE_BACKWARD, MOVE_LEFT, MOVE_RIGHT, TURN_LEFT, TURN_RIGHT, LINE_DETECT
}Status;
/*
typedef enum {
	HIGH, LOW, MEDIUM
}Gesture;
*/
typedef enum {
	ONLINE, ONCURVE_BEGIN, ONCURVE_MIDDLE, ONCURVE_END
}Place;

typedef enum{
	INITIAL,STAGE, PLATFORM, ONPLATFORM,SLOPE
}Stage; 
struct RoboTurtle {
	Status status = INITIALIZE;
	//Gesture gesture = MEDIUM;
	Place place = ONLINE;
	Stage stage = INITIAL;
	
	bool takeTurn = false;
	int step_cnt = 0;
	Data turtle;

	int walkStep = 0;
	double Angle = 0;
	float Distance = 0;
	//bool ultraOn = true;
	void upPlatform();
	void takeAction();
	void upStairs();
};

void RoboTurtle::upPlatform(){
	stay_Middle();
	sleep(1);
	Move_forward(150);
	Move_forward(150);
	Move_forward(150);
	Move_forward(150);
	Move_forward(150);
	Move_forward(150);
	Move_forward(150);
	Move_forward(150);
	Move_forward(150);
	Move_forward(150);
	Move_forward(150);
	Move_right(50);
	stay_Middle();
	//sleep(3);
	Stand_up();
	stay_HIGH();
	
	Move_forward_high();
	Move_forward_high();
	Move_forward_high();
	//Move_forward_high();
	
	//waitKey(0);*/
	stay_HIGH();
	//sleep(3);
	Stand_up2();
	stay_High();
	Up_platform();
}

void RoboTurtle::upStairs(){
	int i = initialSteps;
	while (i--)
		Move_forward(200);
}
void RoboTurtle::takeAction() {
	switch (status) {
	case INITIALIZE:{
		turtle = CapLine();
		if(turtle.degrees > 0) Turn_right(int(turtle.degrees));
		else Turn_left(int(-turtle.degrees));
		//upStairs();
		status = LINE_DETECT;
		break;
	}
	case MOVE_FORWARD: {
		switch(stage){
			case STAGE:
				stay_Middle_stage();
				break;
			default:
				stay_Middle();
		}
		cout << "MOVE_FORWARD" << endl;
		//if(ultraOn){
			Distance = disMeasure(); 
			if (Distance < UpDistance&& stage != INITIAL && stage != STAGE && stage != SLOPE) {
				cout<< "UP_PLATFORM"<<endl;
				upPlatform();
				stage = ONPLATFORM;
				//ultraOn = false;
				step_cnt = 0;
			}
		//} 
		if(takeTurn){
			int tt = turnTimes ;
			if(fabs(Angle)>40) tt+=1;
			
			//Move_forward();
			//Move_forward();
			if(Angle < 0)
				while(tt--)
					Turn_left(-int(Angle/turnCoefficient));
			else 
				while(tt--)
					Turn_right(int(Angle/turnCoefficient));
			Move_forward(turtle.distance);
			takeTurn = false;
			status = LINE_DETECT;
			break;
		}
		
		
		
		cout << step_cnt <<endl;
		switch(stage){
		case STAGE:{
			Up_stairs();
			step_cnt++;
			if(step_cnt>StairSteps && stage == STAGE)
				stage = PLATFORM;
			break;
		}
		case ONPLATFORM:{
			Move_forward(200);
			step_cnt++;
			if(step_cnt == PlatformSteps ){
				Down_platform();
				stage = SLOPE;
			}
			break;
		}
		default:{
			Move_forward(turtle.distance);
			step_cnt++;
			if(step_cnt>initialSteps && stage == INITIAL)
				stage = STAGE;
			break;
		}
		//status = LINE_DETECT;
		}
		
		
		status = LINE_DETECT;
		break;
	}
	case LINE_DETECT: {
		switch(stage){
			case STAGE:
				stay_Middle_stage();
				break;
			default:
				stay_Middle();
		}
		cout << "DETECTING_LINE" << endl;
		turtle = CapLine();
		if ((turtle.degrees > -interimDegree && turtle.degrees < 0) || (turtle.degrees > 0 && turtle.degrees < interimDegree)) {
			Angle = turtle.degrees;
			status = MOVE_FORWARD;
			break;
		}
		else if (turtle.degrees < -interimDegree && turtle.degrees >= -90) {
			place = ONCURVE_BEGIN;
			status = TURN_LEFT;
			Angle = turtle.degrees;
			break;
		}
		else if (turtle.degrees > interimDegree && turtle.degrees <= 90) {
			place = ONCURVE_BEGIN;
			status = TURN_RIGHT;
			Angle = turtle.degrees;
			break;
		}
		else if (turtle.degrees > 100000 && turtle.degrees < 250000) {
			if (turtle.degrees == 200000) {
			/*if (Angle < -interimDegree && Angle >= -90) {
				place = ONCURVE_BEGIN;
				status = TURN_RIGHT;
				Angle = -Angle;
				//Angle = turtle.degrees;
				break;
			}
			else if (Angle > interimDegree && Angle <= 90) {
				place = ONCURVE_BEGIN;
				status = TURN_LEFT;
				Angle = -Angle;
				//Angle = turtle.degrees;
				break;
			}
			else*/
				status = MOVE_BACKWARD;
				break;
			}
			else 
				turtle.degrees -= 200000;
			if(turtle.degrees > 0)
				status = MOVE_RIGHT;
			else
				status = MOVE_LEFT;
			break;
		}
		else if (turtle.degrees > 250000) {
			takeTurn = true;
			status = MOVE_FORWARD;
			Angle = turtle.degrees - 300000;
			place = ONCURVE_BEGIN;
			/*if ((turtle.degrees > -interimDegree && turtle.degrees < 0) || (turtle.degrees > 0 && turtle.degrees < interimDegree)) {
				Angle = turtle.degrees;
				status = STAY;
				break;
			}
			if (turtle.degrees < -interimDegree && turtle.degrees >= -90) {
				status = TURN_LEFT;
				Angle = turtle.degrees;
				break;
			}
			else if (turtle.degrees > interimDegree && turtle.degrees <= 90) {
				status = TURN_RIGHT;
				Angle = turtle.degrees;
				break;
			}*/
		}
		break;
	}
	case MOVE_RIGHT: {
		cout << "MOVE_RIGHT" << turtle.degrees<<" INDEXS"<<endl;
		switch(stage){
			case STAGE:
				Move_right_stage(turtle.degrees);
				break;
			default:
				Move_right(turtle.degrees);//stay_Middle();
		}
		status = LINE_DETECT;
		break;
	}
	case MOVE_LEFT: {
		cout << "MOVE_LEFT" << turtle.degrees<<" INDEXS"<<endl;
		switch(stage){
			case STAGE:
				Move_left_stage(-turtle.degrees);
				break;
			default:
				Move_left(-turtle.degrees);
		}
		status = LINE_DETECT;
		break;
	}
	case TURN_RIGHT: {
		cout << "TURN_RIGHT " << Angle << " DEGREES" << endl;
		int tt = 2;
		
		switch(stage){
			case STAGE:
				while (tt--)
					Turn_right_stage(int(Angle/turnCoefficient));
				break;
			default:
				while (tt--)
					Turn_right(int(Angle/turnCoefficient));
				break;
		}
		status = LINE_DETECT;
		break;
	}
	case TURN_LEFT: {
		cout << "TURN_LEFT " << Angle << " DEGREES" << endl;
		int tt = 2;
		
		switch(stage){
			case STAGE:
				while (tt--)
					Turn_left_stage(int(Angle/turnCoefficient));
				break;
			default:
				while (tt--)
					Turn_left(int(Angle/turnCoefficient));
				break;
		}
		status = LINE_DETECT;
		break;
	}
	case MOVE_BACKWARD: {
		cout << "MOVE_BACKWARD" <<endl;
		Move_backward();
		status = LINE_DETECT;
		break;
	}
	}
}

#endif
