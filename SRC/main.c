#include "main.h"

int main(void)
{

  MVcmd JScmd;
  int i;
 
  switch(StartUP()){ 
 
  case 1 : //RC Mode 
    
    //Construct JScmd===============
    JScmd.gear = FORWARD;
    JScmd.speed = 0;
    JScmd.dir =  KEEP;
    JScmd.deg = 0;
    //==============================

    //Main loop(RC Mode)===========================
    while(1){
      GetJSinfo2MVcmd(&JScmd);
      Move(JScmd.gear, JScmd.speed, JScmd.dir);
    }
    //=============================================

    //Release Jscmd
    CloseJoystick();    
    break;

  case 2 : //Robot Mode

    sleep(2); // Wait to start until 2 seconds 

    //Main loop(Robot Mode)======================================================
    while(1){
      LRFDistance(lrf, LRF_ALL_ID);
      if(LRFShow(LRF_FRONT_ID,lrf[LRF_FRONT_ID].datasize,lrf[LRF_FRONT_ID].data,5000,"FRONT LRF") == 27)
	break;
    }    
    /* while(1){ */
    /*   GetEncData(&FCEnc,&RREnc,&RLEnc); */
    /*   printf("%d\t%d\t%d\n",FCEnc,RREnc,RLEnc); */
    /* } */
    //===========================================================================

    //Close LRF connection     
    CloseLRF(lrf, LRF_ALL_ID);
    //Rlease LRFShow
    CloseLRFShow(LRF_ALL_ID);
    break;
  }

  CloseArduino(AR_ALL_ID);
 
  return 0;
}


int StartUP(void)
{
  char flg;

  puts("------------------------------------------------------------");
  puts("\t\tWelcome to KIT-C1 program !!");
  puts("------------------------------------------------------------");

  //Select the Mode=========================================================================
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
  //=========================================================================================

  //Connection Set up============================================
  //Arduino setup
  if(!SetArduino(AR_ALL_ID));
  else{
    puts("Arduino Connect is Failed....");
    exit(1);
  }

  switch(flg){
  case '1' :
    //Joy Stick set up
    if(SetJoystick()){
      puts("JoyStick Connect is Failed....");
      exit(1);
    }
    break;

  case '2' :
    //LRF set up
    if(SetLRF(lrf, LRF_ALL_ID)){
      puts("LRF Connect is Failed....");
      exit(1);
    }
    //LRFShow set up
    if(SetLRFShow(LRF_ALL_ID)){
      puts("LRFShow Set up is Failed....");
      exit(1);
    }
  } 


  //===============================================================


  switch(flg){
  case '1' :
    puts("");
    puts("------------------------------------------------------------");
    puts("\t\tStart the RC Mode.\n\t\tGood Luck !! ('o')ﾉｼ");
    puts("------------------------------------------------------------");
    break;
 
  case '2' :
    puts("");
    puts("------------------------------------------------------------");
    puts("\t\tStart the Robot Mode.\n\t\tLet's Go !! ('o')ﾉｼ");
    puts("------------------------------------------------------------");
    break;

  default :
    break;
  }

  return atoi(&flg);
}
