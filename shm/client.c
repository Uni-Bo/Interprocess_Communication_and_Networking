#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "buffer.h"

void handler(int signal)
{
return;
}

void main()
{
	signal(SIGCONT,handler);
	int shmid = shmget(1234,sizeof(buffer),IPC_CREAT|0666);
	buffer * Buffer= (buffer*)shmat(shmid,NULL,0);
	//buff_init(Buffer);
	
	Buffer->cpid=getpid();
	while(Buffer->spid==-10);
	
	char input[300];
	
	printf("Enter a string: ");
	scanf("%s",input);
	strcpy(Buffer->buff,input);
	kill(Buffer->spid,SIGCONT);
	pause();
	printf("The string is %s",Buffer->buff);
	
	shmdt((void*)Buffer);
}
