#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char ch = 'A';

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = 8086;
	len = sizeof(address);
	
	connect(sockfd, (struct sockaddr *)&address,len);
	
	char stream[1024];
	printf("enter a bitstream: ");
	scanf(" %s",stream);

	send(sockfd,stream,strlen(stream),0);
	memset(stream,'\0',sizeof(stream));

	read(sockfd,stream,sizeof(stream));
	printf("Recived: %s\n",stream);
	close(sockfd);
}




