#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

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

#define LED_IO 0 
#define KEY_IO 1 

int setup_gpio()
{
    wiringPiSetup();
	

	pinMode (KEY_IO,INPUT ) ;//key button
	pinMode (LED_IO,OUTPUT ) ; //led
	digitalWrite(LED_IO, LOW);//初始化就on


    return 1;
}

int main()
{
	int sleepcnt =0;
	char flag =0;
    if (!setup_gpio()) {
        printf("Cannot initalize gpio");
        return 1;
    }

    while (1) {
      if((digitalRead(KEY_IO) != 1)){
		usleep(5000);
		sleepcnt =0;
		flag =0;
		if((digitalRead(KEY_IO) != 1)){
			//printf("button press \n");
			 while(digitalRead(KEY_IO) != 1){
				 sleepcnt ++;
				 usleep(500000);
			 }
			 while(!digitalRead(KEY_IO));
			 //printf("button %d \n",sleepcnt);
			 if(sleepcnt < 3)
			 {
				 digitalWrite(LED_IO, HIGH);//初始化就on
				 system("sudo poweroff");
			 }else if(sleepcnt >= 8)
			 {
				 flag =1;
				 system("sudo /opt/create_ap.sh");
			 }
		 
	   }
	  }
	  if(flag == 1)
	  {
		  digitalWrite(LED_IO, LOW);
		  usleep(500000);
		  digitalWrite(LED_IO, HIGH);
		  usleep(500000);
	  }
    }
 

    return 0;
}


 
