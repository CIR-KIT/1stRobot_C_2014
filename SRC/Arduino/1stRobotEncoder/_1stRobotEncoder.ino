#include <TimerOne.h>

#define BAUDRATE 115200
#define DATASIZE 24

#define FCA 2  //Front Center A
#define FCB 3  //Front Center B
#define FCZ 4  //Front Center Z
#define RRA 5  //Rear Right A
#define RRB 6  //Rear Right B
#define RRZ 7  //Rear Right Z
#define RLA 8  //Rear Left A
#define RLB 9  //Rear Left B
#define RLZ 10 //Rear Left Z

typedef struct{
  unsigned char A[2];
  unsigned char B[2];
  unsigned char Z[2];
  unsigned short data;
} EncData;

EncData FC;
EncData RR;
EncData RL;
char SendData[DATASIZE];

void MakeCmd(char *data, const EncData fc, const EncData rr, const EncData rl);

void setup(void)
{
  for(int i=FCA; i<=RLZ; i++){
    pinMode(i,INPUT);
    digitalWrite(i,HIGH);
  } 
  
  Timer1.initialize();
  Timer1.attachInterrupt(Encoder,50);
 
  FC.A[0] = (unsigned char)digitalRead(FCA);
  FC.B[0] = (unsigned char)digitalRead(FCB);
  FC.data = 0;
  RR.A[0] = (unsigned char)digitalRead(RRA);
  RR.B[0] = (unsigned char)digitalRead(RRB);
  RR.data = 0;
  RL.A[0] = (unsigned char)digitalRead(RLA);
  RL.B[0] = (unsigned char)digitalRead(RLB);
  RL.data = 0;
  
  Serial.begin(BAUDRATE);
}

void loop(void)
{
  MakeCmd(SendData, FC, RR, RL);
  for(char i=0; i<DATASIZE; i++)
      while(Serial.write(SendData[i]) != 1);
}

void Encoder(void)
{ 
  FC.A[1] = (unsigned char)digitalRead(FCA);
  FC.B[1] = (unsigned char)digitalRead(FCB);
  RR.A[1] = (unsigned char)digitalRead(RRA);
  RR.B[1] = (unsigned char)digitalRead(RRB);
  RL.A[1] = (unsigned char)digitalRead(RLA);
  RL.B[1] = (unsigned char)digitalRead(RLB);
 
  if( (FC.A[0] != FC.A[1]) || (FC.B[0] != FC.B[1]) ){
    switch((FC.B[0] + FC.A[1])%2){
      case 1 :
        FC.data++;
        break;
      default :
        FC.data--;
        break;
    }
  }

  if( (RR.A[0] != RR.A[1]) || (RR.B[0] != RR.B[1]) ){
    switch((RR.B[0] + RR.A[1])%2){
     case 1 :
       RR.data++;
       break;
     default :
       RR.data--;
       break;
    }
  }
  
  if( (RL.A[0] != RL.A[1]) || (RL.B[0] != RL.B[1]) ){
    switch((RL.B[0] + RL.A[1])%2){
      case 1 :
        RL.data++;
        break;
      default :
        RL.data--;
        break;
    }
  }
  
  FC.A[0] = FC.A[1];
  FC.B[0] = FC.B[1];
  RR.A[0] = RR.A[1];
  RR.B[0] = RR.B[1];
  RL.A[0] = RL.A[1];
  RL.B[0] = RL.B[1];
}

void MakeCmd(char *data, const EncData fc, const EncData rr, const EncData rl)
{ 
  sprintf(data,"$ENC,%d%d%d%d%d,%d%d%d%d%d,%d%d%d%d%d;",
   fc.data/10000, fc.data/1000%10, fc.data/100%10, fc.data/10%10, fc.data%10,
   rr.data/10000, rr.data/1000%10, rr.data/100%10, rr.data/10%10, rr.data%10,
   rl.data/10000, rl.data/1000%10, rl.data/100%10, rl.data/10%10, rl.data%10);
}
