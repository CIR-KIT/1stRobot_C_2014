#ifndef __LRF__
#define __LRF__

#define NUM_OF_LRF 1
#define LRF_ALL_ID 9
#define LRF_FRONT_ID 0
#define LRF_REAR_ID 1
#define CAPTURE_TIMES 1

typedef struct{
  long* data;
  long* intensity;
  long datasize;
} LRFData;

int SetLRF(LRFData* lrf, int id);
int LRFDistance(LRFData *lrf, int id);
void CloseLRF(LRFData *lrf, int id);

#endif
