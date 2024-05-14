#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <pthread.h>
struct sockaddr_in client;

void *sender(void * arg){
	int sockfd=*(int*) arg;
	
	char buff[512];
	while(1){
		printf("Enter: ");
		bzero(buff,sizeof(buff));
		scanf(" %[^\n]s",buff);
		sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,sizeof(client));
		if(strcmp("QUIT",buff)==0)
			break;
	}
	exit(0);
}

void *recieve(void* arg){
	int sockfd=*(int*) arg;
	char buff[512];
	socklen_t len=sizeof(client);
	while(1){
		bzero(buff,sizeof(buff));
		recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,&len);
		printf("\33[2k\rRecieved: %s\nEnter: ",buff);
		if(strcmp("QUIT",buff)==0){
			printf("\33[2k\r");
			strcpy(buff,"QUIT");
			sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,sizeof(client));
			break;
		}
		fflush(stdout);
	}
	exit(0);
}


void main(int argc,char ** argv){
	if(argc<4){
		printf("Provide reciever IP your own port and reciever port number!");
		exit(1);
	}
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[2]));
	server.sin_addr.s_addr=INADDR_ANY;
	
	client.sin_family=AF_INET;
	client.sin_port=htons(atoi(argv[3]));
	client.sin_addr.s_addr=inet_addr(argv[1]);
	
	int sockfd=socket(AF_INET,SOCK_DGRAM,0);
	bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	pthread_t t1,t2;
	pthread_create(&t1,NULL,sender,(void*)&sockfd);
	pthread_create(&t2,NULL,recieve,(void*)&sockfd);
	pthread_exit(NULL);
	
}

