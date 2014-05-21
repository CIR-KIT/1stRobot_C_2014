/*-----------------------------------------------------------
  Name    : arduino.c
  Version : Ver 1.5
  Date    : 2014/03/21 (Ver 1.0) First Release
            2014/03/29 (Ver 1.5) Change Arduino path (by id)
  Author  : Ryodo Tanaka (Kyushu Institute of Technology)
  About   : Comunicate with arduino,like...
            to move the robot, the LRF,
	    or to get encoder (or any sensor) data.
-------------------------------------------------------------*/

//local include
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "arduino.h"

//for debug
#define printLOG( msg ) fprintf(stderr,"file : %s\tline : %d\tmessage : %s\n",__FILE__,__LINE__,msg)

//local settings 
#define BAUDRATE B115200           //Baudrate
#define SENDSIZE 13                //Send data size (Byte)
#define RECVSIZE 10                //Recieve data size (Byte)

//Serial Port path
const char* PORT[NUM_OF_ARDUINO] = {"/dev/serial/by-id/usb-Arduino__www.arduino.cc__0043_95233353131351B0B131-if00
", "/dev/ttyACM1"};

//File discripter for Arduino
int ARfd[NUM_OF_ARDUINO];

//Old & New serial settings for Arduino                          
struct termios ARoldtio[NUM_OF_ARDUINO], ARnewtio[NUM_OF_ARDUINO];

/*-----------------------------------------------------------
  Name     : SetArduino
  Argument : int id (Arduino ID)
  Return   : 0 (success) other(failed) 
  About    : Setup the serial settings of Arduino 
  Version  : Ver 1.0
  Date     : 2014/03/21
  Author   : Ryodo Tanaka (Kyushu Institute of Technology)
------------------------------------------------------------*/
int SetArduino(const int id)
{
  //File open
  if( (ARfd[id] = open(PORT[id], O_RDWR)) < 0){
    printLOG("File Open Arduino");
    return 1;
  }

  //Get old serial settings of Arduino
  ioctl(ARfd[id], TCGETS, &ARoldtio[id]);
  //Copy old to new 
  ARnewtio[id] = ARoldtio[id];

  //New serial settings of Arduino
  ARnewtio[id].c_cflag = (BAUDRATE | CS8 | CREAD | CLOCAL);
  ARnewtio[id].c_iflag = (IGNPAR | ICRNL);
  ARnewtio[id].c_oflag = 0;
  ARnewtio[id].c_lflag = ~ICANON;

  //Set new serial settings of Arduino
  ioctl(ARfd[id], TCSETS, &ARnewtio[id]);

  return 0;
}

/*-----------------------------------------------------------
  Name     : CloseArduino
  Argument : int id
  Return   : void
  About    : close file
  Version  : Ver 1.0
  Date     : 2014/03/21
  Author   : Ryodo Tanaka (Kyushu Institute of Technology)
-------------------------------------------------------------*/
void CloseArduino(int id){
  close(ARfd[id]);
}

/*---------------------------------------------------------------
  Name     : Move
  Argument : DIRflg, speed, STEERflg
  Return   : 0(succeed), other(failed)
  About    : Send Move command(SENDSIZE byte) to Arduino
             Move command chart (speed value) is "000" to "256")
	       Forward  :  $MV,F(speed calue),S(+or-or@);
	       Back     :  $MV,B(speed value),S(+or-or@);
	       Stop     :  $MV,F(speed value),S(+or-or@);
	                   $MV,B(speed value),S(+or-or@);
	       Right    :  $MV,F(speed value),S+;
	                   $MV,B(speed value),S+;
	       Left     :  $MV,F(speed value),S-;
	                   $MV,B(speed value),S-;
	       Keep     :  $MV,F(speed value),S@;
	                   $MV,B(speed value),S@;
  Version  : Ver 1.0
  Date     : 2014/03/21
  Author   : Ryodo Tanaka (Kyushu Institute of Technology)
----------------------------------------------------------------*/
int Move(const char DIRflg, const unsigned char speed, const char STEERflg)
{
  char buf[SENDSIZE] = {'.'};

  if(DIRflg != 'F' && DIRflg != 'B') return 1;
  else if(speed < 0 || 220 < speed) return 2;
  else if(STEERflg != '+' && STEERflg != '-' && STEERflg != '@') return 3;
  else{
    sprintf(buf, "$MV,%c%d%d%d,S%c;", DIRflg, speed/100,speed/10%10, speed%10 ,STEERflg);
    while(write(ARfd[SEND_ID], buf, SENDSIZE) != SENDSIZE);
  }
  return 0;
}

int ReadEncoder()
{
}
