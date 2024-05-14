#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <pthread.h>
struct sockaddr_in br_addr,send_addr;
#define unicast_addr "127.0.0.1"
int sockfd,sockfd2;

void *sender(void * arg){

	char buff[512];
	while(1){
		bzero(buff,sizeof(buff));
		scanf(" %[^\n]s",buff);
		sendto(sockfd2,buff,sizeof(buff),0,(struct sockaddr*)&send_addr,sizeof(send_addr));
		if(strcmp("QUIT",buff)==0){
			printf("\33[2k\r");
			break;
		}
	}
	exit(0);
}

void *recieve(void* arg){

	char buff[512];
	socklen_t len=sizeof(br_addr);
	while(1){
		bzero(buff,sizeof(buff));
		recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&br_addr,&len);
		printf("\33[2k\rRecieved: %s\n: ",buff);
		if(strcmp("QUIT",buff)==0){
			printf("\33[2k\r");
			break;
		}
	}
	exit(0);
}


void main(int argc,char ** argv){
	if(argc<3){
		printf("Provide broadcast IP and  port number!");
		exit(1);
	}

	
	br_addr.sin_family=AF_INET;
	br_addr.sin_port=htons(atoi(argv[2]));
	br_addr.sin_addr.s_addr=inet_addr(argv[1]);
	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	int reuse=1;
	int res=setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
	if(res<0){
		perror("\nError ");
		exit(1);
	}
	res=bind(sockfd,(struct sockaddr*)&br_addr,sizeof(br_addr));
	if(res<0){
		perror("\nBind Error ");
		exit(1);
	}
	
	sockfd2=socket(AF_INET,SOCK_DGRAM,0);
	send_addr.sin_family=AF_INET;
	send_addr.sin_port=htons(atoi(argv[3]));
	send_addr.sin_addr.s_addr=inet_addr(unicast_addr);
	setsockopt(sockfd2,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
	pthread_t t1,t2;
	pthread_create(&t1,NULL,sender,(void*)&sockfd2);
	pthread_create(&t2,NULL,recieve,(void*)&sockfd);
	pthread_exit(NULL);


}
