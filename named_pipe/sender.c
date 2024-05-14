/*
3 parts to the named pipe

1. make the pipe using the mkfifo command.
2. open the pipe using open(name of fifo, O_WRONLY/O_RDONLY) 
3. READ/WRITE in the pipe read(nameof pipe, data, size of data), write(nameof
 	pipe, data, size of data +1)
 	
specify the path along with the file name to access the named pipe
*/


// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int fd;

	// FIFO file path
	char * myfifo = "/home/debanjan/Desktop/Debanjan/practice/named_pipe/pipe1";

	// Creating the named file(FIFO)
	// mkfifo(<pathname>, <permission>)
	mkfifo(myfifo, 0666);

	char arr1[80];

		// Open FIFO for write only
		fd = open(myfifo, O_WRONLY);

		// Take an input arr2ing from user.
		// 80 is maximum length
		fgets(arr1, 80, stdin);
		
		// Write the input arr2ing on FIFO
		// and close it
		write(fd, arr1, strlen(arr1)+1);
		//sleep(5);
		close(fd);

	
	return 0;
}

