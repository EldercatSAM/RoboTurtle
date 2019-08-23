#pragma once
#ifndef TURTLE_H
#define TURTLE_H

#include "/home/pi/RoboTurtle/Turtle/servo/walk.c"
#include "/home/pi/RoboTurtle/Turtle/servo/turn.c"
#include "/home/pi/RoboTurtle/Turtle/servo/cross_country.c"
#include "/home/pi/RoboTurtle/Turtle/line/line.cpp"

#define interimDegree 14
#define sleeptime 0.8

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
			sleep(sleeptime);
			
			status = LINE_DETECT;
			break;
		}
		case MOVE_FORWARD: {
			Move_forward();
			status = STAY;
			break;
		}
		case LINE_DETECT: {
			double lineDetect = CapLine();
			if ((lineDetect > -interimDegree && lineDetect < 0) || (lineDetect > 0 && lineDetect < interimDegree)) {
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
			break;
		}
		case MOVE_RIGHT: {
			Move_right();
			status = STAY;
			break;
		}
		case MOVE_LEFT: {
			Move_left();
			status = STAY;
			break;
		}
		case TURN_RIGHT: {
			Turn_right(int(Angle));
			status = STAY;
			break;
		}
		case TURN_LEFT: {
			Turn_left(int(-Angle));
			status = STAY;
			break;
		}

	}
}

#endif
