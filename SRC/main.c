#include "main.h"

int main(void)
{

  MVcmd JScmd;
  
  //constract JScmd
  JScmd.gear  = FORWARD;
  JScmd.speed = 0;
  JScmd.dir   = KEEP;
  JScmd.deg   = 0;
  
  //Open Joy Stick
  SetJoystick();
  //Open Arduino
  SetArduino(SEND_ID);
  SerArduino(RECV_ID);

  //Main Roop
  while(1){
    GetJSinfo2MVcmd(&JScmd);
    Move(JScmd.gear, JScmd.speed, JScmd.dir);
  }

  //Close Arduino
  CloseArduino(SEND_ID);
  CloseArduino(RECV_ID);
  //Close JoyStick
  CloseJoystick();

  return 0;
}
