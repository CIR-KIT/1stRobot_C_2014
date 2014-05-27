/*-----------------------------------------------------------
  Name    : lrf.c
  Version : Ver 1.0
  Date    : 2014/05/25 (Ver 1.0) First Release
  Author  : Ryodo Tanaka (Kyushu Institute of Technology)
  About   : Communicate with LRF includes Serial & Ethernet
-------------------------------------------------------------*/
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

/*-----------------------------------------------------------
  Name     : SetLRF
  Argument : LRFData *lrf, int id (LRF ID)
  Return   : 0 (success) other(failed) 
  About    : Setup the serial settings of LRF 
  Version  : Ver 1.0
  Date     : 2014/05/25
  Author   : Ryodo Tanaka (Kyushu Institute of Technology)
------------------------------------------------------------*/
int SetLRF(LRFData* lrf, const int id)
{
  int i;

  if(id == LRF_CPY_ID){
    for(i=0; i<NUM_OF_LRF; i++){
      //Get max numbers of lrf_data
      lrf[i].datasize = urg_max_data_size(&urg[i]);

      //Get Memory for lrf_data with calloc
      lrf[i].data = (long*)calloc(lrf[i].datasize,sizeof(long));
      if(!lrf[i].data){
	perror("calloc");
	exit(1);
      }
    }
  }
  else if(id == LRF_ALL_ID){
    for(i=0; i<NUM_OF_LRF; i++){
      //Open LRF Device (Serial)
      if (urg_open(&urg[i], URG_SERIAL,SERIAL_PORT[i],115200) < 0) {
	if(urg_open(&urg[i], URG_ETHERNET,ETHER_PORT[i],19208) < 0){
	  printLOG("urg_open()");
	  exit(1);
	}
      }

      //Get max numbers of lrf_data
      lrf[i].datasize = urg_max_data_size(&urg[i]);

      //Get Memory for lrf_data with calloc
      lrf[i].data = (long*)calloc(lrf[i].datasize,sizeof(long));
      if(!lrf[i].data){
	perror("calloc");
	exit(1);
      }
    }
  }
  
  else{
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
  }

  puts("LRF is Connected...");

  return 0;
}

  /*-----------------------------------------------------------
    Name     : CloseLRF
    Argument : LRFData* lrf, int id
    Return   : void
    About    : close LRF connection & free lrf.data
    Version  : Ver 1.0
    Date     : 2014/05/25
    Author   : Ryodo Tanaka (Kyushu Institute of Technology)
    -------------------------------------------------------------*/
  void CloseLRF(LRFData *lrf, const int id)
  {
    int i;

    if(id == LRF_CPY_ID){
      for(i=0; i<NUM_OF_LRF; i++)
	free(lrf[i].data);
    }
    else if(id == LRF_ALL_ID){
      for(i=0; i<NUM_OF_LRF; i++){
	free(lrf[i].data);
	urg_close(&urg[i]);
      }
    }
    else {
      free(lrf->data);
      urg_close(&urg[id]);
    }
  }

  /*-----------------------------------------------------------
    Name     : LRFDistance
    Argument : LRFData* lrf, int id
    Return   : 0(succeed), other(failed)
    About    : Get distance data of LRF
    Version  : Ver 1.0
    Date     : 2014/05/25
    Author   : Ryodo Tanaka (Kyushu Institute of Technology)
    -------------------------------------------------------------*/
int LRFDistance(LRFData *lrf, const int id)
{
  long time_stamp[NUM_OF_LRF];
  int i;

  if(id == LRF_ALL_ID){
    for(i=0; i<NUM_OF_LRF; i++){
      //Start to get LRF Data
      urg_start_measurement(&urg[i], URG_DISTANCE, CAPTURE_TIMES, 0);

      //Get LRF Data "CAPTURE_TIMES" times
      pthread_mutex_lock(&LRFMTX[i]);
      if(urg_get_distance(&urg[i], lrf[i].data, &time_stamp[i]) <=0){
	printLOG("urg_get_data()");    
	urg_close(&urg[i]);
	exit(1);
      }
      pthread_mutex_unlock(&LRFMTX[i]);
    }
  }
  else {
    //Start to get LRF Data
    urg_start_measurement(&urg[id], URG_DISTANCE, CAPTURE_TIMES, 0);

    //Get LRF Data "CAPTURE_TIMES" times
    pthread_mutex_lock(&LRFMTX[id]);
    if(urg_get_distance(&urg[id], lrf->data, &time_stamp) <=0){
      printLOG("urg_get_data()");    
      urg_close(&urg[id]);
      exit(1);
    }
    pthread_mutex_unlock(&LRFMTX[id]);
  }

  return 0;
}
