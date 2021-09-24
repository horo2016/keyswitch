#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <iostream> 
#include <string>
#include <vector>
#include"wiringPi.h"
#include <assert.h>
#include <sys/select.h>
#include <fcntl.h>   //low_level i/o
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>


int setup_gpio()
{
    wiringPiSetup();
	

	pinMode (0,INPUT ) ;//key button
	pinMode (1,OUTPUT ) ; //led
	digitalWrite(1, LOW);//初始化就on


    return true;
}

int main_sonar()
{
	int sleepcnt =0;
	char flag =0;
    if (!setup_gpio()) {
        printf("Cannot initalize gpio");
        return 1;
    }

    while (1) {
      if((digitalRead(0) != 1)){
	    usleep(8000);
		sleepcnt =0;
		flag =0;
	   if((digitalRead(0) != 1)){
	     while((digitalRead(0) != 1){
			 sleepcnt ++;
			 usleep(500000);
			 while(!digitalRead(0));
			 if(sleepcnt < 3)
			 {
				 digitalWrite(1, HIGH);//初始化就on
				 system("sudo poweroff");
			 }else if(sleepcnt >= 8)
			 {
				 flag =1;
				 system("sudo /home/opt/create_ap.sh")
			 }
		 }
	   }
	  }
	  if(flag == 1)
	  {
		  digitalWrite(1, LOW);
		  usleep(500000);
		  digitalWrite(1, HIGH);
		  usleep(500000);
	  }
    }
 

    return 0;
}


 
