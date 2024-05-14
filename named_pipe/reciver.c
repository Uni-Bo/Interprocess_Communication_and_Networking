
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



		// Open FIFO for Read only
		fd = open(myfifo, O_RDONLY);

		// Read from FIFO
		read(fd, arr1, sizeof(arr1));

		// Print the read message
		printf("User2: %s\n", arr1);
		//sleep(5);
		close(fd);

	
	return 0;
}


		
