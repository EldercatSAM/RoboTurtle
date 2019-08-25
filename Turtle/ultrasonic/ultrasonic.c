#include <wiringPi.h>  
#include <stdio.h>  
#include <sys/time.h>  
#define Trig    4  
#define Echo    5  
  
void ultraInit(void)  
{  
    pinMode(Echo, INPUT);  //设置端口为输入
    pinMode(Trig, OUTPUT);  //设置端口为输出
}  
  
float disMeasure(void)  
{  
    struct timeval tv1;  //timeval是time.h中的预定义结构体 其中包含两个一个是秒，一个是微秒
    /*
    struct timeval
    {
        time_t tv_sec;  //Seconds. 
        suseconds_t tv_usec;  //Microseconds. 
    };
    */
    
    struct timeval tv2;  
    long start, stop;  
    float dis;  
  
    digitalWrite(Trig, LOW);  
    delayMicroseconds(2);  
  
    digitalWrite(Trig, HIGH);  
    delayMicroseconds(10);      //发出超声波脉冲  
    digitalWrite(Trig, LOW);  
      
    while(!(digitalRead(Echo) == 1));  
    gettimeofday(&tv1, NULL);           //获取当前时间 开始接收到返回信号的时候 
  
    while(!(digitalRead(Echo) == 0));  
    gettimeofday(&tv2, NULL);           //获取当前时间  最后接收到返回信号的时候
    /*
    int gettimeofday(struct timeval *tv, struct timezone *tz);
    The functions gettimeofday() and settimeofday() can get and set the time as well as a timezone. 
    The use of the timezone structure is obsolete; the tz argument should normally be specified as NULL.
    */
    start = tv1.tv_sec * 1000000 + tv1.tv_usec;   //微秒级的时间  
    stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;  
  
    dis = (float)(stop - start) / 1000000 * 34000 / 2;  //计算时间差求出距离  
  
    return dis;  
}  
  
int main(void)  
{  
    float dis;  
  
    if(wiringPiSetup() == -1){ //如果初始化失败，就输出错误信息 程序初始化时务必进行
        printf("setup wiringPi failed !");  
        return 1;   
    }  
  
    ultraInit();  
      
    while(1){  
        dis = disMeasure();  
        printf("distance = %0.2f cm\n",dis);  
        delay(1000);  
    }  
  
    return 0;  
}
