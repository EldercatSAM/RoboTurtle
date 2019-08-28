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
#define turnCoefficient 1.1
#define UpDistance 45
typedef enum {
	STAY, MOVE_FORWARD, MOVE_BACKWARD, MOVE_LEFT, MOVE_RIGHT, TURN_LEFT, TURN_RIGHT, LINE_DETECT
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
	Status status = LINE_DETECT;
	//Gesture gesture = MEDIUM;
	Place place = ONLINE;
	bool takeTurn = false;
	int step_cnt = 0;
	Data turtle;

	int walkStep = 0;
	double Angle = 0;
	float Distance = 0;
	void upPlatform();
	void takeAction();
};

void RoboTurtle::upPlatform(){
	stay_Middle();
	sleep(1);
	Move_forward();
	Move_forward();
	Move_forward();
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

void RoboTurtle::takeAction() {
	switch (status) {
	case STAY: {
		//stay_Middle();
		
		cout << "STAYING" << endl;
		//sleep(sleeptime);
		if (!takeTurn){
			if (place == ONLINE)
				walkStep += 2;
			else
				walkStep += 2; // wait for edit!!!!
			status = MOVE_FORWARD;
			//break;
		}
		else {
			int tt = turnTimes ;
			if(fabs(Angle)>40) tt+=1;
			/*if(Angle < 0)
				Turn_left(-int(Angle/turnTimes));
			else 
				Turn_right(int(Angle/turnTimes));*/
			//Move_forward();
			//Move_forward();
			if(Angle < 0)
				while(tt--)
					Turn_left(-int(Angle/turnCoefficient));
			else 
				while(tt--)
					Turn_right(int(Angle/turnCoefficient));
			Move_forward();
			Move_forward();
			Move_forward();
			takeTurn = false;
			status = LINE_DETECT;
			break;
		}
		/*case ONCURVE_MIDDLE: {
			walkStep += 2;
			place = ONCURVE_END;
			break;
		}
		case ONCURVE_END: {
			walkStep += 4;
			place = ONLINE;
			break;
		}	 */
		//status = LINE_DETECT;
		break;
	}
	case MOVE_FORWARD: {
		stay_Middle();
		Distance = disMeasure(); 
		if (Distance < UpDistance){
			cout<< "UP_PLATFORM"<<endl;
			upPlatform();
			waitKey(0); 
		} 
		cout << "MOVE_FORWARD" << endl;
		cout << walkStep <<endl;
		while (walkStep>0){
			Move_forward();
			walkStep--;
		}
		status = LINE_DETECT;
		break;
	}
	case LINE_DETECT: {
		stay_Middle();
		cout << "DETECTING_LINE" << endl;
		turtle = CapLine();
		if ((turtle.degrees > -interimDegree && turtle.degrees < 0) || (turtle.degrees > 0 && turtle.degrees < interimDegree)) {
			Angle = turtle.degrees;
			step_cnt++;
			if(step_cnt > 2){
				place = ONLINE;
				step_cnt = 0;
			}
			status = STAY;
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
			status = STAY;
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
		Move_right(turtle.degrees);
		status = LINE_DETECT;
		break;
	}
	case MOVE_LEFT: {
		cout << "MOVE_LEFT" << turtle.degrees<<" INDEXS"<<endl;
		Move_left(-turtle.degrees);
		status = LINE_DETECT;
		break;
	}
	case TURN_RIGHT: {
		cout << "TURN_RIGHT " << Angle << " DEGREES" << endl;
		int tt = 2;
		while (tt--)
			Turn_right(int(Angle/turnCoefficient));
		status = LINE_DETECT;
		break;
	}
	case TURN_LEFT: {
		cout << "TURN_LEFT " << Angle << " DEGREES" << endl;
		int tt = 2;
		while (tt--)
			Turn_left(int(-Angle/turnCoefficient));
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
