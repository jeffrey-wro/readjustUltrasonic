#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>

#include "MyRio.h"
#include "I2C.h"
#include "Motor_Controller.h"
#include "Utils.h"

using namespace std;

extern NiFpga_Session myrio_session;

NiFpga_Status status;
void distanceInit(int low, int high);
void updateDistance();
int getDistance();
int dd;

int main(int argc, char **argv)
{
  

	distanceInit(15,20);//range of sensor

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
	//int delay = 3;

	int leftCount = 0;
	int rigthCount = 0;

	//update the sensor every 3 seconds

	for(int i=0; i<25; i++){
		dd = getDistance();
		if(dd < 10)
		{
			rigthCount -= 465;
			mc.setMotorDegrees(DC, 0, leftCount, speed, rigthCount);
		}else{
			leftCount -= 360;
			rigthCount += 360;
			mc.setMotorDegrees(DC, speed, leftCount, speed, rigthCount);
			
		}
		Utils::waitFor(1);

	}
	Utils::waitFor(2);
	

	mc.controllerReset(DC);
	mc.controllerReset(SERVO);

	status = MyRio_Close();

	return status;


	return 0;
}

void distanceInit(int low, int high)
{
	//set the initial distance between range of sensor which is 2cm and 450 cm
	dd = ((rand()%(high - low )) + low); //whatever function it is

}

void updateDistance()
{
	//add a small number of change
	dd += ((rand()%(5 - -5)) + -5); //whatever function it is
	fflush(stdout);
}

///get distance in cm
int getDistance()
{
	updateDistance();
	printf("GetDisatnce: %d\n",dd);
	fflush(stdout);

	return dd;
}

