#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#include "buffer.h"

int main ()
{
	int shmid= shmget(1001,sizeof(buffer),IPC_CREAT|0666);
	buffer * Buffer = (buffer*)shmat(shmid,NULL,0);
	buffer_init(Buffer);
	
	Buffer->spid=getpid();
	while(Buffer->rpid==-10);
	int Signal_send=SIGUSR1;
	
	if(kill(Buffer->rpid, Signal_send)==0)
	{
	 	printf("Signal sent");
	}
	else
	{
		printf("Error");
	}
return 0;
}
