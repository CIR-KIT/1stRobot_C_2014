#include "main.h"
#include <stdio.h>

int main(void)
{

  MVcmd JScmd;
  EncCmd cnt;
  
  //constract JScmd
  JScmd.gear  = FORWARD;
  JScmd.speed = 0;
  JScmd.dir   = KEEP;
  JScmd.deg   = 0;
  
  //Open Joy Stick
  //  SetJoystick();
  //Open Arduino
  // SetArduino(SEND_ID);
  SetArduino(RECV_ID);

 

  //Main Roop
  while(1){
    //GetJSinfo2MVcmd(&JScmd);
    //Move(JScmd.gear, JScmd.speed, JScmd.dir);
    ReadEncoder(&cnt);
    printf("%d\t%d\t%d\n",cnt.cmd[0], cnt.cmd[1], cnt.data);
  }

  //Close Arduino
  //CloseArduino(SEND_ID);
  CloseArduino(RECV_ID);
  //Close JoyStick
  //CloseJoystick();

  return 0;
}
