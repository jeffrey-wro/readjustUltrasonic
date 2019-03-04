#include "Ultrasonic.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#include "DIO.h"
#include "MyRio.h"

using namespace std;

Ultrasonic::Ultrasonic(){

    B0.dir = DIOB_70DIR;
    B0.out = DIOB_70OUT;
    B0.in = DIOB_70IN;
    B0.bit = 0;

    B1.dir = DIOB_70DIR;
    B1.out = DIOB_70OUT;
    B1.in = DIOB_70IN;
    B1.bit = 1;

}


int Ultrasonic::getDistance(){

    int duration;
    int distance;

    struct timeval t1;
    struct timeval t2;


        dio_B0 = 0;
        Dio_WriteBit(&B0, dio_B0);
        usleep(2);
        dio_B0 = 1;
        Dio_WriteBit(&B0, dio_B0);
        usleep(10);
        dio_B0 = 0;
        Dio_WriteBit(&B0, dio_B0);


        while(Dio_ReadBit(&B1) == 0);
        gettimeofday(&t1, NULL);
        while(Dio_ReadBit(&B1) != 0);
        gettimeofday(&t2, NULL);

        duration = t2.tv_usec-t1.tv_usec;
        distance = (duration / 2) * 0.0343;

    return distance;
}