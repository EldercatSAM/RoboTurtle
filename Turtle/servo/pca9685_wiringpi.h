
#ifndef PCA9685_WIRINGPI_H
#define PCA9685_WIRINGPI_H
#include "/home/pi/RoboTurtle/Turtle/servo/wiringPiI2C.h"
//#include <wiringPi.h>
#include <unistd.h>


#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4
#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE
#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9
#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD

#define ServoNum 12
/*
理解：
通过WiringPi i2c通信控制pca9685 pca9685再生成相应频率信号，控制舵机
这是一个基于WiringPi编写的pca9685库，包括两个函数 初始化 pca9685_init 和控制某一通道pca9685_setmk
十六路通道看似有48个IO口，实际上有32个是VCC/GND，我们只控制一十六个IO口。
第一步是设置时钟（initial）。根据公式计算出prescale值，再根据pca9685手册步骤进入睡眠模式，完成设置后重启
然后就可以分别发送数据到每一个通道，从而pca9685按照设置好的prescale输出周期性变化的pwm信号，达到控制舵机的效果。
----------------------------------------------------------------------
MODE1寄存器
位	名称	功能
D7	RESTART	写1复位，写完后此位自动清除。一定要在SLEEP位写0后至少500us后才能对此位写1进行复位。
D6	EXTCLOCK	0-使用内部时钟（25MHz）。1-使用外部时钟引脚的时钟。修改此位前，一定要先SLEEP，再修改此位（此时SLEEP位仍然写1），再退出SLEEP。
D5	AI	0-内部地址读写后不自动增加。1-内部地址读写后自动增加。一般i2c设备在对从机读写后内部地址都会自动增加，这个芯片可以手动设置是否自动增加，我们一般都会设成自动增加。
D4	SLEEP	0-退出SLEEP模式。1-进入SLEEP模式。注：1、写0退出sleep模式后，最多等500us后即可产生稳定的时钟信号。2、写1进入sleep模式后，时钟会关闭。此时可以修改时钟源寄存器EXTCLOCK和周期寄存器PRE_SCALE，修改这两个寄存器之前必须先进入sleep模式。
D3	SUB1
D2	SUB2
D1	SUB3
D0	ALLCALL	0-不响应0x70通用i2c地址。1-响应0x70通用i2c地址。这个芯片除了可以通过A5:A0自定义i2c地址外，还有一个通用i2c地址0x70，此寄存器可以控制是否响应这个通用地址。注意啊：这个寄存器的设置好像掉电会保存的！
*/
int pca9685;
int pca9685_init(unsigned char addr)	// addr是7位的i2c从机地址，返回的是linux标准的设备描述符，调用它的地方视作pca9685的设备描述符
//因为可以多个pca9685级联，通过设备描述符区别它们
//此驱动仅作为驱动舵机使用，周期固定死位20ms，不允许外部设置
{

	pca9685 = wiringPiI2CSetup(addr);
	{	//初始化pca9685芯片
		double T = 20000;	//周期，单位是us
		unsigned char prescale;
		double osc_clock = 25000000;
		unsigned char oldmode, newmode;
		T /= 0.915;	//不知道为什么，会有所偏差，这里校准一下就ok了，从网上找的arduino代码也进行了校准。
		T /= 1000000;	//把T转换成秒
		prescale = (unsigned char)(osc_clock / 4096 * T - 1);
		//	printf("prescale = 0x%x", prescale);
		oldmode = wiringPiI2CReadReg8(pca9685, PCA9685_MODE1);
		newmode = (oldmode & 0x7f) | 0x10;	//第一位 置0，第四位 置1 //保持不重启，准备进入sleep模式（设置时钟前必须先进入sleep模式）

		wiringPiI2CWriteReg8(pca9685, PCA9685_MODE1, newmode);
		wiringPiI2CWriteReg8(pca9685, PCA9685_PRESCALE, prescale);
		oldmode &= 0xef;	//清除sleep位
		wiringPiI2CWriteReg8(pca9685, PCA9685_MODE1, oldmode);
		sleep(0.005);
		wiringPiI2CWriteReg8(pca9685, PCA9685_MODE1, oldmode | 0xa1);
	}
	return pca9685;
}
void pca9685_setmk(int fd, int num, int mk)	//设置指定通道的脉宽。fd是在pca9685_init时获得的设备描述符，num是通道号（从0开始），mk是脉宽单位是us。周期已经固定为20ms了
{
	unsigned int ON, OFF;
	ON = 0;	//每次周期一开始就输出高电平
	OFF = (unsigned int)((((double)mk) / 20000 * 4096)*1.0067114);	//最后的1.0067114是校准用的
	// printf("off = 0x%x", OFF);
	wiringPiI2CWriteReg16(fd, LED0_ON_L + 4 * num, ON);
	wiringPiI2CWriteReg16(fd, LED0_OFF_L + 4 * num, OFF);
	/*
	int wiringPiI2CWriteReg16(int fd, int reg, int data);
	往从机指定的reg写2个字节，先传输低8位，后传输高8位。
	<起始> + <从机地址W> + <reg> + <data低8位> + <data高8位> + <结束>
	*/
}

#endif
