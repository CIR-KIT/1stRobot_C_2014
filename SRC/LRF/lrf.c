//local include
#include <stdio.h>
#include <urg_sensor.h>
#include <urg_utils.h>

#include "lrf.h"

//for debug
#define printLOG( msg ) fprintf(stderr,"mesg : %s\nfile : %s\nline : %d\n",msg,__FILE__,__LINE__)

//local define
const char* PORT[NUM_OF_LRF] = {"/dev/ttyACM2"};

int LRFSet(urg_t* urg)
{



  return 0;
}
