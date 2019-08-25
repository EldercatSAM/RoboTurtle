#include <wiringPi.h>  
#include <stdio.h>  
#include <sys/time.h>  
#define Trig    4  
#define Echo    5  
  
void ultraInit(void)  
{  
    pinMode(Echo, INPUT);  //���ö˿�Ϊ����
    pinMode(Trig, OUTPUT);  //���ö˿�Ϊ���
}  
  
float disMeasure(void)  
{  
    struct timeval tv1;  //timeval��time.h�е�Ԥ����ṹ�� ���а�������һ�����룬һ����΢��
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
    delayMicroseconds(10);      //��������������  
    digitalWrite(Trig, LOW);  
      
    while(!(digitalRead(Echo) == 1));  
    gettimeofday(&tv1, NULL);           //��ȡ��ǰʱ�� ��ʼ���յ������źŵ�ʱ�� 
  
    while(!(digitalRead(Echo) == 0));  
    gettimeofday(&tv2, NULL);           //��ȡ��ǰʱ��  �����յ������źŵ�ʱ��
    /*
    int gettimeofday(struct timeval *tv, struct timezone *tz);
    The functions gettimeofday() and settimeofday() can get and set the time as well as a timezone. 
    The use of the timezone structure is obsolete; the tz argument should normally be specified as NULL.
    */
    start = tv1.tv_sec * 1000000 + tv1.tv_usec;   //΢�뼶��ʱ��  
    stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;  
  
    dis = (float)(stop - start) / 1000000 * 34000 / 2;  //����ʱ����������  
  
    return dis;  
}  
  
int main(void)  
{  
    float dis;  
  
    if(wiringPiSetup() == -1){ //�����ʼ��ʧ�ܣ������������Ϣ �����ʼ��ʱ��ؽ���
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
