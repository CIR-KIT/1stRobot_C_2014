//Stundard include
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Local include
#include "main.h"

//for debug
#define printLOG( msg ) fprintf(stderr,"mesg : %s\nfile : %s\nline : %d\n",msg,__FILE__,__LINE__)

int main(void)
{

  MVcmd JScmd;
  int i;
 
  switch(StartUP()){ 
 
  case 1 : //RC Mode 
    //Joy Stick set up
    if(SetJoystick()){
      puts("JoyStick Connect is Failed....");
      exit(1);
    }
    //Construct JScmd===============
    JScmd.gear = FORWARD;
    JScmd.speed = 0;
    JScmd.dir =  KEEP;
    JScmd.deg = 0;
    //==============================

    //Arduino Setup
    if(!SetArduino(AR_SEND_ID));
    else{
      puts("SEND Arduino Connect is Failed....");
      exit(1);
    }

    puts("");
    puts("------------------------------------------------------------");
    puts("\t\tStart the RC Mode.\n\t\tGood Luck !! ('o')ﾉｼ");
    puts("------------------------------------------------------------");
    //Main loop(RC Mode)===========================
    while(1){
      GetJSinfo2MVcmd(&JScmd);
      Move(JScmd.gear, JScmd.speed, JScmd.dir);
    }
    //=============================================

    //Release Jscmd
    CloseJoystick();
    //Close Arduino connection
    CloseArduino(AR_SEND_ID);    
    break;

  case 2 : //Robot Mode
    //create thread================================================
    if(!pthread_create(&LRFThreadID, NULL, LRFThread,NULL))
      puts("LRFThread is created...");
    else{
      printLOG("LRFThread create");
      exit(1);
    }

    if(!pthread_create(&EncoderThreadID, NULL, EncoderThread,NULL))
      puts("EncoderThread is created...");
    else{
      printLOG("EncoderThread create");
      exit(1);
    }
    //=============================================================

    //LRFShow set up
    if(SetLRFShow(LRF_ALL_ID)){
      puts("LRFShow Set up is Failed....");
      exit(1);
    }

    // Wait to start until 2 seconds 
    sleep(2); 

    puts("");
    puts("------------------------------------------------------------");
    puts("\t\tStart the Robot Mode.\n\t\tLet's Go !! ('o')ﾉｼ");
    puts("------------------------------------------------------------");

    //Main loop(Robot Mode)======================================================
    while(1){
      //puts("here");
      for(i=0; i<NUM_OF_LRF; i++){
	pthread_mutex_lock(&LRFMTX[i]);
	lrfCpy[i] = lrf[i];
	pthread_mutex_unlock(&LRFMTX[i]);
      }
      if(LRFShow(LRF_FRONT_ID,lrfCpy[LRF_FRONT_ID].datasize,lrfCpy[LRF_FRONT_ID].data,5000,"FRONT LRF") == 27)
	break;
    }
    //===========================================================================

    //Rlease LRFShow
    CloseLRFShow(LRF_ALL_ID);
    break;
  }

 
  return 0;
}

void* LRFThread(void *arg)
{
  //LRF set up
  if(SetLRF(lrf, LRF_ALL_ID)){
    puts("LRF Connect is Failed....");
    exit(1);
  }
  //Copy data setup
  if(SetLRF(lrfCpy, LRF_CPY_ID)){
    puts("LRF Copy data error");
    exit(1);
  }

  //LRF Thread loop
  while(1){
    LRFDistance(lrf, LRF_ALL_ID);
  }

  //Close LRF connection     
  CloseLRF(lrf, LRF_ALL_ID);
  //Close LRF connection     
  CloseLRF(lrfCpy, LRF_CPY_ID);
}

void* EncoderThread(void *arg)
{ 
  //Arduino Setup
  if(!SetArduino(AR_RECV_ID));
  else{
    puts("Recev Arduino Connect is Failed....");
    exit(1);
  }

  //Encoder Thread loop
  while(1){
    GetEncData(&FCEnc,&RREnc,&RLEnc);

    pthread_mutex_lock(&EncoderMTX);
    FCEncCpy = FCEnc;
    RREncCpy = RREnc;
    RLEncCpy = RLEnc;
    pthread_mutex_unlock(&EncoderMTX);
    printf("%d\t%d\t%d\n",FCEncCpy,RREncCpy,RLEncCpy);
  }  

  //Close Arduino
  CloseArduino(AR_RECV_ID);
}

int StartUP(void)
{
  char flg;

  puts("------------------------------------------------------------");
  puts("\t\tWelcome to KIT-C1 program !!");
  puts("------------------------------------------------------------");

  while(flg != '1' && flg != '2'){
    puts("Select the Mode.");
    puts("RC    Mode...1\nRobot Mode...2");
    if(scanf("%c%*c",&flg) < 0)
      flg = 0;

    if(flg == '1'){
      puts("");
      puts("------------------------------------------------------------");
      puts("\t\tRC Mode is selected.");
      puts("------------------------------------------------------------");
      puts("");
    }
    else if(flg == '2'){
      puts("");
      puts("------------------------------------------------------------");
      puts("\t\tRobot Mode is selected.");
      puts("------------------------------------------------------------");
      puts("");
    }
    else{
      puts("\t\t!! Input Collect selection !!");
      puts("");
    }
  }
  return atoi(&flg);
}
