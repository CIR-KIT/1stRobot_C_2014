#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <cv.h>
#include <highgui.h>

#include "./LRF/lrf.h"
#include "./LRF/SHOW/lrfshow.h"
#include "./Arduino/arduino.h"
#include "./Control/control.h"

int StartUP(void);

unsigned short FCEnc, RREnc, RLEnc;
 
