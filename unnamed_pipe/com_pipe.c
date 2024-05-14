#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//3 sections to the program

/* 
1. declareing variable and creating the pipe
2. creating fork(unnamed pipe only works on parent child)
3. comunicating using pipe

help-- man pipe
*/

/*
where 
read(pipefd[0], buffer, size_of_buffer)
weite(pipefd[1], buffer, size_of_buffer)
*/

int main()
{
	int pipefd[2];// 
	pid_t cpid;
	char buff[256], input[256];
	
	if (pipe(pipefd) == -1)
	{
		printf("Failed to create pipe");
		return 0;
	}
	
	cpid = fork();
	if (cpid == -1 )
	{
		printf ("Failed to fork");
		return 0;
	}
	
	if (cpid==0)
	{
		//reading from pipe, so closing the write end
		close(pipefd[1]);
		read(pipefd[0],buff, sizeof(buff));
		printf("Recived in child: %s",buff);
		close(pipefd[0]);
	}
	else
	{
		
		//writing in pipe, so closing the read end
		close(pipefd[0]);
		printf("Enter what to input ");
		scanf("%s",input);
		write(pipefd[1],input, sizeof(input));
		close(pipefd[1]);
	}
	return 0;		
}
	
