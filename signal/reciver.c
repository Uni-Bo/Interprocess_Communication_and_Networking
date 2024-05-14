#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#include "buffer.h"

void signalHandler(int signal_)
{
	if (signal_==SIGUSR1)
	{
		printf("recived signal from sender");
	}
}

int main ()
{
	int shmid= shmget(1001,sizeof(buffer),IPC_CREAT|0666);
	buffer * Buffer = (buffer*)shmat(shmid,NULL,0);
	//buffer_init(Buffer);
	
	Buffer->rpid=getpid();
	while(Buffer->spid==-10);
	signal(SIGUSR1, signalHandler);
	
	sleep(15);
return 0;
}
