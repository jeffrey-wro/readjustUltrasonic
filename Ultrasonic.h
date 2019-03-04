#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "DIO.h"
#include "MyRio.h"

class Ultrasonic
{
public:
	Ultrasonic();
	int getDistance();
private:
	NiFpga_Bool dio_B0;
    NiFpga_Bool dio_B1;

    MyRio_Dio B0;
    MyRio_Dio B1;

};

#endif
