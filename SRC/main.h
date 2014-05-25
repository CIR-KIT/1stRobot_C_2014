//Stundard include
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Local include
#include "./LRF/lrf.h"
#include "./LRF/SHOW/lrfshow.h"
#include "./Arduino/arduino.h"
#include "./Control/control.h"

//Local function (main)
int StartUP(void);

unsigned short FCEnc, RREnc, RLEnc;    //Encoder data => FC...FrontCenter, RR...RearRight, RL...RearLeft
LRFData lrf[NUM_OF_LRF];                           //LRF data (distance, intensity, datasize)
