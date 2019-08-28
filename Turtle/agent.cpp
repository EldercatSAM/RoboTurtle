#include "/home/pi/RoboTurtle/Turtle/Turtle_Agent.h"

/*
cd RoboTurtle/Turtle
g++ -o agent agent.cpp `pkg-config --cflags --libs opencv` -I/usr/local/include -L/usr/local/lib -lwiringPi

*/
int main() {
	if(wiringPiSetup() == -1){ //Èç¹û³õÊ¼»¯Ê§°Ü£¬¾ÍÊä³ö´íÎóÐÅÏ¢ ³ÌÐò³õÊ¼»¯Ê±Îñ±Ø½øÐÐ
        printf("setup wiringPi failed !");  
        return 1;   
    }  
	ultraInit(); 
	pca9685 = pca9685_init(0x40);
	RoboTurtle Sam;
	while (1) {
		Sam.takeAction();
	}
}
