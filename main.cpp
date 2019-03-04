#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>

#include "MyRio.h"
#include "I2C.h"
#include "Motor_Controller.h"
#include "Utils.h"
#include "Ultrasonic.h"

#include <sys/time.h>

using namespace std;

extern NiFpga_Session myrio_session;

void waitForMilli (int usecs);

NiFpga_Status status;

int dd;

int main(int argc, char **argv)
{
  
    Ultrasonic ultrasonic;


	status = MyRio_Open();
	if (MyRio_IsNotSuccess(status))
	{
		return status;
	}

	MyRio_I2c i2c;
	status = Utils::setupI2CB(&myrio_session, &i2c);

	Motor_Controller mc = Motor_Controller(&i2c);
	mc.controllerEnable(DC);
	mc.controllerEnable(SERVO);

	int volt = mc.readBatteryVoltage(1);
	printf("%d\n\n", volt);


	int speed = 200;

	int rigthCount = 0;

	int loopTime = time(0) + 20; 
	while(time(0) < loopTime){
	
		//mc.setMotorSpeeds(DC, 0, 0);

		dd = ultrasonic.getDistance();

		if(dd < 30)
		{

			rigthCount -= 465;
			mc.setMotorDegrees(DC, 0,0, speed, rigthCount);
			Utils::waitFor(2);
			printf("%d, Turning\n", dd);
		}else{

			mc.setMotorSpeeds(DC, speed, -speed);
			//leftCount += 360;
			//rigthCount -= 360;
			//mc.setMotorDegrees(DC, speed, leftCount, speed, rigthCount);
			
			printf("%d, Forward\n", dd);

		}
		fflush(stdout);

		Utils::waitFor(1);

		//for(int i=100000000; i >0; i--);

	}

	mc.controllerReset(DC);
	mc.controllerReset(SERVO);

	status = MyRio_Close();

	return status;


	return 0;
}


void waitForMilli (int milli_seconds) {
  
    // Stroing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds);
  
}