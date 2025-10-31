typedef struct {
    char* processName;
    int time;
}process;

//circular buffer declaration
#define BUFFERSIZE  10
process buffer[BUFFERSIZE];

//Declaration of access pointers
int start=0, end=0;

//Function to add process to buffer
void addProc(char *nname, int ntime){

  //Verification of position (full?)
  if ( ((end+1)%BUFFERSIZE) != start){
    //Current position update
    buffer[end].processName = nname;
    buffer[end].time = ntime;
    //increment circular buffer position
    end = (end+1)%(BUFFERSIZE);
  }
}

//Function to remove process from buffer
void removeProc (void){

  //Verification of position (empty?)
  if (end != start){
    //increment circular buffer start position
    start = (start +1)%(BUFFERSIZE);
  }

}

#include "stdio.h"
void main (void){
  addProc("proc1", 0);
  addProc("proc2", 1);
  addProc("proc3", 2);
  removeProc();
  removeProc();
  removeProc();
}


