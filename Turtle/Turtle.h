#pragma once
#ifndef TURTLE_H
#define TURTLE_H

#include "/home/pi/RoboTurtle/Turtle/servo/walk.c"
#include "/home/pi/RoboTurtle/Turtle/servo/turn.c"
#include "/home/pi/RoboTurtle/Turtle/servo/cross_country.c"
#include "/home/pi/RoboTurtle/Turtle/line/line.cpp"

#define interimDegree 20
#define sleeptime 0.3

typedef enum {
	STAY, MOVE_FORWARD, MOVE_BACKWARD, MOVE_LEFT, MOVE_RIGHT, TURN_LEFT, TURN_RIGHT, LINE_DETECT
}Status;

typedef enum {
	HIGH, LOW, MEDIUM
}Gesture;

struct RoboTurtle {
	Status status = STAY;
	Gesture gesture;

	double Angle = 0;

	void takeAction();
};

void RoboTurtle::takeAction() {
	switch (status) {
		case STAY: {
			stay_Middle();
			//sleep(sleeptime);
			cout<<"STAYING"<<endl;
			status = LINE_DETECT;
			break;
		}
		case MOVE_FORWARD: {
			cout<<"MOVE_FORWARD"<<endl;
			Move_forward();
			Move_forward();//Two steps at once-.-
			status = STAY;
			break;
		}
		case LINE_DETECT: {
			cout<<"DETECTING_LINE"<<endl;
			double lineDetect = CapLine();
			if ((lineDetect > -interimDegree && lineDetect < 0) || (lineDetect > 0 && lineDetect < interimDegree)) {
				Angle = lineDetect;
				status = MOVE_FORWARD;
				break;
			}
			else if (lineDetect < -interimDegree && lineDetect >= -90) {
				status = TURN_LEFT;
				Angle = lineDetect;
				break;
			}
			else if (lineDetect > interimDegree && lineDetect <= 90) {
				status = TURN_RIGHT;
				Angle = lineDetect;
				break;
			}
			else if (lineDetect == 199909) {
				status = MOVE_RIGHT;
				break;
			}
			else if (lineDetect == 200012) {
				status = MOVE_LEFT;
				break;
			}
			else if (lineDetect == 200000) {
				if (Angle< -interimDegree && Angle >= -90) {
					status = TURN_LEFT;
					//Angle = lineDetect;
					break;
				}
				else if (Angle > interimDegree && Angle <= 90) {
					status = TURN_RIGHT;
					//Angle = lineDetect;
					break;
				}
				else
					status = MOVE_BACKWARD;
				break;
			}
			break;
		}
		case MOVE_RIGHT: {
			cout<<"MOVE_RIGHT"<<endl;
			Move_right();
			status = STAY;
			break;
		}
		case MOVE_LEFT: {
			cout<<"MOVE_LEFT"<<endl;
			Move_left();
			status = STAY;
			break;
		}
		case TURN_RIGHT: {
			cout<<"TURN_RIGHT "<<Angle<<" DEGREES"<<endl;
			Turn_right(int(Angle));
			status = STAY;
			break;
		}
		case TURN_LEFT: {
			cout<<"TURN_LEFT "<<Angle<<" DEGREES"<<endl;
			Turn_left(int(-Angle));
			status = STAY;
			break;
		}
		case MOVE_BACKWARD: {
			cout<<"MOVE_BACKWARD";
			Move_backward();
			status = STAY;
			break;
		}
	}
}

#endif
