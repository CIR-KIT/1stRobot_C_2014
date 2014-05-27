//Local include
#include "./LRF/lrf.h"
#include "./LRF/SHOW/lrfshow.h"
#include "./Arduino/arduino.h"
#include "./Control/control.h"

//Local function (main)
int StartUP(void);

unsigned short FCEnc, RREnc, RLEnc;                //Encoder data => FC...FrontCenter, RR...RearRight, RL...RearLeft
unsigned short FCEncCpy, RREncCpy, RLEncCpy;       //Copy of the Encoder datas
LRFData lrf[NUM_OF_LRF];                           //LRF data (distance, intensity, datasize)
LRFData lrfCpy[NUM_OF_LRF];                        //Copy of the LRFData lrf


//pthread=====================================
#ifndef __PTHREAD__
#define __PTHREAD__
#include <pthread.h>
#endif

//Thread function
void* LRFThread(void* arg);
void* EncoderThread(void* arg);

//pthread ID
pthread_t LRFThreadID;
pthread_t EncoderThreadID;

//pthread mutex ID
pthread_mutex_t LRFMTX[NUM_OF_LRF];
pthread_mutex_t EncoderMTX;

//===========================================
