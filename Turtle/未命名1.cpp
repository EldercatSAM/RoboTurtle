 
#include <sys/time.h>  
#include <bits/stdc++.h>
using namespace std;

int main() {
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
    gettimeofday(&tv1, NULL); 
    int i =20000000; 
    sleep(1);
	while (i--);
	 gettimeofday(&tv2, NULL); 
	 float dis = (float)(stop - start) / 1000000; 
	 printf("distance = %0.2f cm\n",dis);
}
