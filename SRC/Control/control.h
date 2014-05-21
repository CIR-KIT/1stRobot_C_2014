#ifndef __CONTROL__
#define __CONTROL__

typedef struct{
  char gear;
  unsigned char speed;
  char dir;
  unsigned char deg;
} MVcmd;

//MVcmd JScmd;

int SetJoystick(void);
void GetJSinfo2MVcmd(MVcmd*);
void CloseJoystick(void);

#endif
