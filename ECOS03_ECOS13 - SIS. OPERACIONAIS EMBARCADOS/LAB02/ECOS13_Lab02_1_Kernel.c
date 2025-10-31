//kernel internal variables
int start, end;
int count = 0;

//return code
#define SUCCESS   0
#define FAIL      1
#define REPEAT    2
#define POOL_SIZE 5

char tst1(void){
   printf("Process 1\n");
   return REPEAT;
}

char tst2(void){
   printf("Process 2\n");
   return SUCCESS;
}

char tst3(void){
   printf("Process 3\n");
   return REPEAT;
}

//function pointer declaration
typedef char(*ptrFunc)(void);

//process struct
typedef struct {
	ptrFunc func;
} process;

process * pool[POOL_SIZE];

char kernelInit(void){
	start = 0;
	end = 0;
	return SUCCESS;
}

char kernelAddProc(process * newProc){
	//checking for free space
	if ( ((end+1)%POOL_SIZE) != start){
		pool[end] = newProc;
		end = (end+1)%POOL_SIZE;
		return SUCCESS;
	}
	return FAIL;
}

void kernelLoop(void){
  for(;;){
    //Do we have any process to execute?
      if (start != end){
        //check if there is need to reschedule
        if (pool[start]->func() == REPEAT){
          kernelAddProc(pool[start]);
        }
        //prepare to get the next process;
        start = (start+1)%POOL_SIZE;
      }
      //count++;
      if (count>=10) break;
   }
}

void main(void){
	//declaring the processes
	process p1 = {tst1};
	process p2 = {tst2};
	process p3 = {tst3};
	kernelInit();
	//Test if the process was added successfully
	if (kernelAddProc(&p1) == SUCCESS){
		printf("1st process added\n");}
	if (kernelAddProc(&p2) == SUCCESS){
		printf("2nd process added\n");}
	if (kernelAddProc(&p3) == SUCCESS){
		printf("3rd process added\n");}
	kernelLoop();
}
