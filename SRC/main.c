#include "main.h"

int main(void)
{
  MVcmd JScmd;
  unsigned short FCEnc, RREnc, RLEnc;
  int flg; 
 
  puts("------------------------------------------------------------");
  puts("\t\tWelcome to KIT-C1 program !!");
  puts("------------------------------------------------------------");

  while(flg != 1 || flg != 2){
    puts("Select the Mode.");
    puts("Robot Mode...1\nRC    Mode...2");
    if(scanf("%d",&flg) < 0)
      flg = 0;

    if(!SetArduino(AR_ALL_ID));
    else{
      puts("Arduino Connect Failed....");
      exit(1);
    }

    if(flg == 1){
      puts("");
      puts("\n\t\tRC Mode is selected.");
      puts("");

      //constract JScmd
      JScmd.gear = FORWARD;
      JScmd.speed = 0;
      JScmd.dir =  KEEP;
      JScmd.deg = 0;
  
      if(!SetJoystick());
      else{
	puts("JoyStick Connect Failed....");
	exit(1);
      }

      puts("\n\t\tStart the RC Mode.");
      puts("");
      puts("\t\tGood Luck !!");

      while(1){
	GetJSinfo2MVcmd(&JScmd);
	Move(JScmd.gear, JScmd.speed, JScmd.dir);
      }
      CloseJoystick();
    }

    else if(flg == 2){
      puts("");
      puts("\t\tRobot Mode is selected.");
      puts("");

      while(1){
	GetEncData(&FCEnc,&RREnc,&RLEnc);
	printf("%d\t%d\t%d\n",FCEnc,RREnc,RLEnc);
      }
    }

    else{
      puts("\t\t!! Input Collect selection !!");
      puts("");
    }

  }


  CloseArduino(AR_ALL_ID);
 

  return 0;
}
