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
	buff_init(Buffer);
	
	Buffer->spid=getpid();
	while(Buffer->cpid==-10);
	
	char recived[300];
	
		pause();
		printf("Recived in server: %s",Buffer->buff);
		int f=1;
		strcpy(recived,Buffer->buff);
		
		int l=0, h=strlen(recived)-1;
		while(h>l)
		{
			if(recived[l++]!=recived[h--])
			{
				f=0;
				break;
			
			}

				
		}
			if(f==0)
				{strcpy(Buffer->buff,"IS NOT palindrom\n");}
			if(f==1)
				{strcpy(Buffer->buff,"IS palindrom\n");}
			
		
		kill(Buffer->cpid, SIGCONT);
		
	shmdt((void *) Buffer);
	shmctl(shmid,IPC_RMID,NULL);

}
