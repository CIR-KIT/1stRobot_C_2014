/*----------------------------------------------------------------
  Name    : 1st Robot Controler
  Version : Ver 2.1
  Date    : 2014/03/21 (Ver 1.0) 初期型(動かず)
            2014/03/22 (Ver 2.0) シリアル通信などを改善(動いた)
            2014/03/22 (Ver 2.1) Forward->Back 改善
  Author  : Ryodo Tanaka (Kyushu Institute of Technology)
  About   : Control 1st Robot
            Use serial communication.
            Move command chart (speed value is "000" to "256")
	       Forward  :  $MV,F(speed calue),S(+or-);
	       Back     :  $MV,B(speed value),S(+or-);
	       Stop     :  $MV,F(speed value),S(+or-);
	                   $MV,B(speed value),S(+or-);
	       Right    :  $MV,F(speed value),S+;
	                   $MV,B(speed value),S+;
	       Left     :  $MV,F(speed value),S-;
	                   $MV,B(speed value),S-;             
              *Move command is 12 Bytes.
------------------------------------------------------------------*/

#define BAUDRATE 115200             //Baudrate
#define DATASIZE 13                 //Move command size (Byte)

char RcvData[DATASIZE] = {'.'};     //Recieve data initialized by '.'

//for Front Stepping Motor (Jservo Stepping Motor controler)
#define CW 3                    
#define CCW 4
#define C0 5
#define C2 6
#define HOFF 7
#define TIME 500    //Delaytime (microseconds)

//for Rear DC Motor 
#define BACK 8
#define ACCEL 9

//Serial flag
boolean serialFLG = false;


void setup(void)
{
  //Setup control pins
  for(char i=CW; i<=ACCEL; i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }
  //Setup serial communication
  Serial.begin(BAUDRATE);
}

//Main
void loop(void)
{
  Move(RcvData);
}

//Serial Interrupt
//This Interrupt Function makes RcvData[0] = '$'
void serialEvent(void)
{
  char buf;

  if(serialFLG == false){
    Serial.end();
    Serial.begin(BAUDRATE);
    serialFLG = true;
  }
  
  for(char i=0; i<DATASIZE; i++){
    while(Serial.available() == 0);
    buf = (char)Serial.read();
    RcvData[i] = buf;
    if(buf == '$'){
      RcvData[0] = buf; 
      i = 0;
    }
  }  
}

//Move function
//Check the command & control the machine
boolean Move(const char* data)
{
  int Speed = 0;
  
  if(data[DATASIZE-2] != ';') return false;
  else if(data[1] != 'M' || data[2] != 'V') return false;
  else if(data[9] != 'S') return false;
  else{
       //forward & back
    switch(data[4]){
      case 'F':
        Speed = atoi(&data[5])*100+atoi(&data[6])*10+atoi(&data[7]);
        switch(digitalRead(BACK)){
          case LOW :
            analogWrite(ACCEL,Speed);
            break;
          case HIGH :
            analogWrite(ACCEL,0);
            delay(700);
            digitalWrite(BACK,LOW);
            delay(400);
            analogWrite(ACCEL,Speed);
            break;
          default :
            break;
        }
        break;
      case 'B':
        Speed = atoi(&data[5])*100+atoi(&data[6])*10+atoi(&data[7]);
        switch(digitalRead(BACK)){
          case HIGH :
            analogWrite(ACCEL,Speed);
            break;
          case LOW :
            analogWrite(ACCEL,0);
            delay(500);
            digitalWrite(BACK,HIGH);
            delay(500);
            analogWrite(ACCEL,Speed);
            break;
          default :
            break;
        }
        break;
      default :
        return false;
        break;
    }
    
    //steer
    switch(data[10]){
      case '+' :
        digitalWrite(CCW,HIGH);
        for(char i=0; i<20; i++){
          digitalWrite(CW,HIGH);
          delayMicroseconds(TIME);  
          digitalWrite(CW,LOW);
          delayMicroseconds(TIME);
        }
        digitalWrite(CCW,LOW);
        break;
      case '-' :
        digitalWrite(CW,HIGH);
        for(char i=0; i<20; i++){ 
          digitalWrite(CCW,HIGH);
          delayMicroseconds(TIME);  
          digitalWrite(CCW,LOW);
          delayMicroseconds(TIME); 
        }
        digitalWrite(CW,LOW);
        break;
      case '@':
        digitalWrite(CW,LOW);
        digitalWrite(CCW,LOW);
        return true;
        break;
      default :
        digitalWrite(CW,LOW);
        digitalWrite(CCW,LOW);
        return false;
        break;      
    }   
  }
  return true;
}

