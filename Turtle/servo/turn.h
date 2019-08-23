#pragma once
#include "/home/pi/RoboTurtle/Turtle/servo/basicfunc.h"

#define rotate_parameter 18
//When this parameter is 16.5 ,it act like a dumb donkey, why so?
//This parameter decides the mapping between degree and the servo value.

void Turn_right(int degree);
void Turn_left(int degree);
