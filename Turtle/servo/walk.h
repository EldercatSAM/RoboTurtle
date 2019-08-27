#pragma once
#ifndef WALK_H
#define WALK_H 

#include "/home/pi/RoboTurtle/Turtle/servo/basicfunc.h"

#define walkCoefficient 2

void Move_forward();
void Move_left(int dis);
void Move_right(int dis);
void Move_backward(); 

#endif
