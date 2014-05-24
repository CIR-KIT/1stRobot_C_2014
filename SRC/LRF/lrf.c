//local include
#include <stdio.h>
#include <stdlib.h>
#include <urg_sensor.h>
#include <urg_utils.h>

#include "lrf.h"

//for debug
#define printLOG( msg ) fprintf(stderr,"mesg : %s\nfile : %s\nline : %d\n",msg,__FILE__,__LINE__)

//local define
const char* SERIAL_PORT[NUM_OF_LRF] = {"/dev/serial/by-id/usb-Hokuyo_Data_Flex_for_USB_URG-Series_USB_Driver-if00"};
const char* ETHER_PORT[NUM_OF_LRF] = {"192.168.0.20"};

//LRF URG 
urg_t urg[NUM_OF_LRF];


int SetLRF(LRFData* lrf, int id)
{
  //Open LRF Device (Serial)
  if (urg_open(&urg[id], URG_SERIAL,SERIAL_PORT[id],115200) < 0) {
    if(urg_open(&urg[id], URG_ETHERNET,ETHER_PORT[id],19208) < 0){
      printLOG("urg_open()");
      exit(1);
    }
  }

  //Get max numbers of lrf_data
  lrf->datasize =urg_max_data_size(&urg[id]);

  //Get Memory for lrf_data with calloc
  lrf->data = (long*)calloc(lrf->datasize,sizeof(long));
  if(!lrf->data){
    perror("calloc");
    exit(1);
  }

  puts("LRF is Connected...");

  return 0;
}

int LRFDistance(LRFData *lrf, int id)
{
  long time_stamp;

  puts("here1");

  //Start to get LRF Data
  urg_start_measurement(&urg[id], URG_DISTANCE, CAPTURE_TIMES, 0);

  puts("here2");

  //Get LRF Data "CAPTURE_TIMES" times
  if(urg_get_distance(&urg[id], lrf->data, &time_stamp) <=0){
    printLOG("urg_get_data()");    
    urg_close(&urg[id]);
    exit(1);
  }

  puts("here3");

  return 0;
}

void CloseLRF(LRFData *lrf, int id)
{
  free(lrf->data);
  urg_close(&urg[id]);
}
