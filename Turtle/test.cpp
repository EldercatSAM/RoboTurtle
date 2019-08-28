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
	sleep(3);
	float dis;
	dis = disMeasure();
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
	Move_forward();
	Move_forward();
	stay_Middle();
	//adjust();
	return 0;
}

