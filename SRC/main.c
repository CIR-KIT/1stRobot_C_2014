#include "main.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
  //  unsigned char i=0;
  MVcmd JScmd;
  
  //constract JScmd
  JScmd.gear = FORWARD;
  JScmd.speed = 0;
  JScmd.dir =  KEEP;
  JScmd.deg = 0;
  
  SetJoystick();
  SetArduino(SEND_ID);
  while(1){
    GetJSinfo2MVcmd(&JScmd);
    Move(JScmd.gear, JScmd.speed, JScmd.dir);
  }

  CloseArduino(SEND_ID);
  CloseJoystick();

  return 0;
}
