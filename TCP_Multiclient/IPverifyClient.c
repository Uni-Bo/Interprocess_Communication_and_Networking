#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

void main(int argc,char ** argv){
	if(argc<3){
		printf("Error! provide IP and port number.\n");
		exit(1);
	}
	
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[2]));
	inet_pton(AF_INET,argv[1],&server.sin_addr);
	
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	connect(sockfd,(struct sockaddr*)&server,sizeof(server));
	char ip[256];
	bzero(ip,sizeof(ip));
	printf("Enter: ");
	scanf(" %s",ip);
	write(sockfd,ip,sizeof(ip));
	bzero(ip,sizeof(ip));
	read(sockfd,ip,sizeof(ip));
	printf("\nResult: %s\n",ip);
	
}
