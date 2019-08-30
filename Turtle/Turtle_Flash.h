#pragma once
#ifndef TURTLE_AGENT_H
#define TURTLE_AGENT_H

#include "/home/pi/RoboTurtle/Turtle/servo/walk.c"
#include "/home/pi/RoboTurtle/Turtle/servo/turn.c"
#include "/home/pi/RoboTurtle/Turtle/line/line.cpp"

#define sleeptime 0.3
#define turnTimes 2
#define turnCoefficient 1.1
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

struct RoboTurtle {
	Status status = INITIALIZE;
	//Gesture gesture = MEDIUM;
	Place place = ONLINE;
	
	bool takeTurn = false;
	int step_cnt = 0;
	Data turtle;

	int walkStep = 0;
	double Angle = 0;
	float Distance = 0;
	//bool ultraOn = true;
	void takeAction();
};

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
		//stay_Middle_stage();
		cout << "MOVE_FORWARD" << endl;
		if(takeTurn){
			int tt = turnTimes ;
			if(fabs(Angle)>40) tt+=1;
			
			//Move_forward();
			//Move_forward();
			if(Angle < 0)
				while(tt--)
					Turn_left_stage(-int(Angle/turnCoefficient));
			else 
				while(tt--)
					Turn_right_stage(int(Angle/turnCoefficient));
			Move_forward_stage(turtle.distance);
			takeTurn = false;
			status = LINE_DETECT;
			break;
		}
		Move_forward_stage(turtle.distance);
		status = LINE_DETECT;
		break;
	}
	case LINE_DETECT: {
		stay_Middle_stage();
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
		Move_right_stage(turtle.degrees);
		status = LINE_DETECT;
		break;
	}
	case MOVE_LEFT: {
		cout << "MOVE_LEFT" << turtle.degrees<<" INDEXS"<<endl;
		Move_left_stage(-turtle.degrees);
		status = LINE_DETECT;
		break;
	}
	case TURN_RIGHT: {
		cout << "TURN_RIGHT " << Angle << " DEGREES" << endl;
		int tt = 2;
		while (tt--)
			Turn_right_stage(int(Angle/turnCoefficient));	
		status = LINE_DETECT;
		break;
	}
	case TURN_LEFT: {
		cout << "TURN_LEFT " << Angle << " DEGREES" << endl;
		int tt = 2;
		while (tt--)
			Turn_left_stage(int(Angle/turnCoefficient));
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
