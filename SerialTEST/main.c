#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define printLOG( msg ) fprintf(stderr,"file : %s\tline : %d\tmessage : %s\n",__FILE__,__LINE__,msg)

#define PORT "/dev/ttyACM2"
#define BAUDRATE B115200
#define DATASIZE 1

int main(void)
{
  char buf[DATASIZE] = {'#'};       //send buffer
  int fd;                     //file discripter
  struct termios pre_term;    //old settings of Serial
  struct termios neo_term;    //new settings of Serial
  int i;

  //File open
  if( (fd = open(PORT, O_RDWR)) == -1){
    printLOG("File Open");
    exit(-1);
  };    

  ioctl(fd, TCGETS, &pre_term);  //Get old settings of Serial
  neo_term = pre_term;           //Copy old to new settings

  //New settings of Serial  
  neo_term.c_cflag = (BAUDRATE | CS8 | CREAD | CLOCAL);
  neo_term.c_iflag = (IGNPAR | ICRNL);
  neo_term.c_oflag = 0;
  neo_term.c_lflag = ~ICANON; 

  ioctl(fd, TCSETS, &neo_term); //Set new settings of Serial

  for(i=0; ;i++){
    if(i%2)
      sprintf(buf,"A");
    else sprintf(buf,"B");
    while(write(fd, buf, DATASIZE) != DATASIZE) puts("here");
    if(i%500)
    usleep(10000);
  }

  ioctl(fd, TCSETS, &pre_term); //Return to old settings of Serial

  close(fd); //Close the port

  return 0;
}
