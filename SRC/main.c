#include "main.h"

int main(void)
{

  MVcmd JScmd;
  LRFData lrf;
  int i;
  IplImage *lrf_img = cvCreateImage(cvSize(LRF_WINDOW_SIZE,LRF_WINDOW_SIZE), IPL_DEPTH_8U, 3);

  switch(StartUP()){
  case 1 : //RC Mode 
    JScmd.gear = FORWARD;
    JScmd.speed = 0;
    JScmd.dir =  KEEP;
    JScmd.deg = 0;
    while(1){
      GetJSinfo2MVcmd(&JScmd);
      Move(JScmd.gear, JScmd.speed, JScmd.dir);
    }
    CloseJoystick();
    break;

  case 2 : //Robot Mode
    SetLRF(&lrf, LRF_FRONT_ID);
    printf("%d\n",malloc_usable_size(lrf.data)/8);
    /* while(1){ */
    /*   LRFDistance(&lrf, LRF_FRONT_ID); */
    /*   puts("Data"); */
    /*   for(i=0; i,lrf.datasize; i++){ */
    /* 	printf("%ld,",lrf.data[i]); */
    /*   } */
    /*   puts(""); */
    //lrf_show(lrf_img,lrf.datasize,lrf.data,5000,"LRF");
    //}    
  /* sleep(2); */
  /* while(1){ */
  /*   GetEncData(&FCEnc,&RREnc,&RLEnc); */
  /*   printf("%d\t%d\t%d\n",FCEnc,RREnc,RLEnc); */
  /* } */
  CloseLRF(&lrf, LRF_FRONT_ID);
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

  //Select the Mode================================================
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
  //==============================================================

  //Connection Set up============================================
  //Arduino setup
  if(!SetArduino(AR_ALL_ID));
  else{
    puts("Arduino Connect Failed....");
    exit(1);
  }

  //Joy Stick set up
  if(flg == '1'){
    if(!SetJoystick());
    else{
      puts("JoyStick Connect Failed....");
      exit(1);
    }
  } else ;
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
