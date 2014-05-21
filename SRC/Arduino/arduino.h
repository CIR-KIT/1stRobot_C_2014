#ifndef __ARDUINO__
#define __ARDUINO__

#define NUM_OF_ARDUINO 2           //Number of Arduino
#define SEND_ID 0                  //ID for send Arduino
#define RECV_ID 1                  //ID for recv Arduino
#define FORWARD 'F'                //Forward command
#define BACK 'B'                   //Back command 
#define RIGHT '+'                  //Turn Right command
#define LEFT '-'                   //Turn Left command
#define KEEP '@'                   //Keep the turn dir

typedef union{
  unsigned char cmd[2];
  unsigned short data;
} EncCmd;

int SetArduino(const int);
void CloseArduino(int);
int Move(const char, const unsigned char , const char);
int ReadEncoder(EncCmd*);

#endif
