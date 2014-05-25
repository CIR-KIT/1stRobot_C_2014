#ifndef __LRF_SHOW__
#define __LRF_SHOW__

#define FIRST_RANGE -45        //First Range of LRF scan [deg]
#define LAST_RANGE 225         //Last Range of LRF scan [deg]
#define LRF_WINDOW_SIZE 500    //Window size of LRFShow

#include "../lrf.h"

int LRFShow(const int id, const long lrf_data_max, const long *lrf_data, const long max_dist, const char* lrf_window_name);
int SetLRFShow(const int id);
void CloseLRFShow(const int id);

#endif
