#pragma once
#ifndef WALK_H
#define WALK_H 

#include "/home/pi/RoboTurtle/Turtle/servo/basicfunc.h"

#define walkCoefficient 1.95
#define moveStep 3.8
#define MinStep 50
#define MaxStep 250

void Move_forward(int dis);
void Move_left(int dis);
void Move_right(int dis);
void Move_backward(); 

#endif
