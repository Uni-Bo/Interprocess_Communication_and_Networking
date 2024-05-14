#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <pthread.h>
#define unicast_addr "127.0.0.1"
struct sockaddr_in br_addr,recv_addr;
int sockfd,sockfd2;

void *sender(void * arg){
	char buff[512];
	while(1){
		printf("Enter: ");
		bzero(buff,sizeof(buff));
		scanf(" %[^\n]s",buff);
		sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&br_addr,sizeof(br_addr));
		if(strcmp("QUIT",buff)==0)
			break;
	}
	exit(0);
}

void *recieve(void* arg){
	char buff[512];
	socklen_t len=sizeof(recv_addr);
	while(1){
		bzero(buff,sizeof(buff));
		recvfrom(sockfd2,buff,sizeof(buff),0,(struct sockaddr*)&recv_addr,&len);
		printf("\33[2k\rRecieved: %s\nEnter: ",buff);
		if(strcmp("QUIT",buff)==0){
			printf("\33[2k\r");
			bzero(buff,sizeof(buff));
			strcpy(buff,"QUIT");
			sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&br_addr,sizeof(br_addr));
			break;
		}
	}
	exit(0);
}



void main(int argc,char ** argv){
	if(argc<4){
		printf("Provide broadcast IP and port numbers!");
		exit(1);
	}

	br_addr.sin_family=AF_INET;
	br_addr.sin_port=htons(atoi(argv[2]));
	br_addr.sin_addr.s_addr=inet_addr(argv[1]);
	
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	int broadcast=1;
	int res=setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&broadcast,sizeof(int));
	if(res<0){
		perror("\nError ");
		exit(1);
	}
	int reuse=1;
	res=setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
	
	sockfd2=socket(AF_INET,SOCK_DGRAM,0);
	recv_addr.sin_family=AF_INET;
	recv_addr.sin_port=htons(atoi(argv[3]));
	recv_addr.sin_addr.s_addr=inet_addr(unicast_addr);;
	setsockopt(sockfd2,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
	res=bind(sockfd2,(struct sockaddr*)&recv_addr,sizeof(recv_addr));
	if(res<0){
		perror("\nError ");
		exit(1);
	}
	pthread_t t1,t2;
	pthread_create(&t1,NULL,sender,NULL);
	pthread_create(&t2,NULL,recieve,NULL);
	pthread_exit(NULL);


}
