#include "/home/pi/RoboTurtle/Turtle/Turtle_Agent.h"

/*
cd RoboTurtle/Turtle
g++ -o test test.cpp `pkg-config --cflags --libs opencv` -I/usr/local/include -L/usr/local/lib -lwiringPi
./test

cd RoboTurtle/Turtle
./test

*/
int main(){
	if(wiringPiSetup() == -1){ //Èç¹û³õÊ¼»¯Ê§°Ü£¬¾ÍÊä³ö´íÎóÐÅÏ¢ ³ÌÐò³õÊ¼»¯Ê±Îñ±Ø½øÐÐ
        printf("setup wiringPi failed !");  
        return 1;   
    }  
	ultraInit(); 
	pca9685 = pca9685_init(0x40);
	//Move_forward();
	
	
	stay_Middle();
	while(1)
		Move_forward();
	//Up_stairs();
	sleep(2);
	//adjust();
	return 0;
}

