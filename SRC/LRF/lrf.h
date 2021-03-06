#ifndef __LRF__
#define __LRF__

#define NUM_OF_LRF 1
#define LRF_FRONT_ID 0
#define LRF_REAR_ID 1
#define LRF_ALL_ID 9
#define CAPTURE_TIMES 1

typedef struct{
  long* data;          //Distance data
  long* intensity;     //Intensity data
  long datasize;       //Number of datas
} LRFData;

int SetLRF(LRFData *lrf, const int id);
int LRFDistance(LRFData *lrf, const int id);
void CloseLRF(LRFData *lrf, const int id);

#endif
