#define BAUDRATE 115200
#define DATASIZE 24

#define FCA 2  //Front Center A
#define FCB 3  //Front Center B
#define FCZ 4  //Front Center Z
#define RLA 5  //Rear Right A
#define RLB 6  //Rear Right B
#define RLZ 7  //Rear Right Z
#define RRA 8  //Rear Left A
#define RRB 9  //Rear Left B
#define RRZ 10 //Rear Left Z

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
  
  attachInterrupt(FCA,FCEncoder,CHANGE);
  attachInterrupt(FCB,FCEncoder,CHANGE);
  attachInterrupt(FCZ,FCEncoder,CHANGE);

  attachInterrupt(RRA,RREncoder,CHANGE);
  attachInterrupt(RRB,RREncoder,CHANGE);
  attachInterrupt(RRZ,RREncoder,CHANGE);

  attachInterrupt(RLA,RLEncoder,CHANGE);
  attachInterrupt(RLB,RLEncoder,CHANGE);
  attachInterrupt(RLZ,RLEncoder,CHANGE);

  FC.A[0] = (unsigned char)digitalRead(FCA);
  FC.B[0] = (unsigned char)digitalRead(FCB);
  FC.Z[0] = (unsigned char)digitalRead(FCZ);
  FC.data = 0;
  RR.A[0] = (unsigned char)digitalRead(RRA);
  RR.B[0] = (unsigned char)digitalRead(RRB);
  RR.Z[0] = (unsigned char)digitalRead(RRZ);
  RR.data = 0;
  RL.A[0] = (unsigned char)digitalRead(RLA);
  RL.B[0] = (unsigned char)digitalRead(RLB);
  RL.Z[0] = (unsigned char)digitalRead(RLZ);
  RL.data = 0;
  
  Serial.begin(BAUDRATE);
}

void loop(void)
{
  MakeCmd(SendData, FC, RR, RL);
  while(Serial.write(SendData) != DATASIZE-1);
}

void FCEncoder(void)
{
  FC.A[1] = (unsigned char)digitalRead(FCA);
  FC.B[1] = (unsigned char)digitalRead(FCB);

 if( (FC.A[0] != FC.A[1]) || (FC.B[0] != FC.B[1]) ){
    if((FC.B[0] + FC.A[1])%2)
      FC.data++;
    else
      FC.data--;
  }

  FC.A[0] = FC.A[1];
  FC.B[0] = FC.B[1];
}

void RREncoder(void)
{
  RR.A[1] = (unsigned char)digitalRead(RRA);
  RR.B[1] = (unsigned char)digitalRead(RRB);

  if( (RR.A[0] != RR.A[1]) || (RR.B[0] != RR.B[1]) ){
    if((RR.B[0] + RR.A[1])%2)
      RR.data++;
    else
      RR.data--;
  }

  RR.A[0] = RR.A[1];
  RR.B[0] = RR.B[1];  
}


void RLEncoder(void)
{ 
  RL.A[1] = (unsigned char)digitalRead(RLA);
  RL.B[1] = (unsigned char)digitalRead(RLB);
    
  if( (RL.A[0] != RL.A[1]) || (RL.B[0] != RL.B[1]) ){
    if((RL.B[0] + RL.A[1])%2)
      RL.data++;
    else
      RL.data--;
  }
  
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
