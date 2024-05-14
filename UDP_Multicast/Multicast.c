#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

struct sockaddr_in Multicast_addr;
int sockfd;

void* senddata(void * arg){
	char buff[512];
	while(1){
		bzero(buff,sizeof(buff));
		printf("\33[2k\rEnter: ");
		scanf(" %[^\n]s",buff);
		sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&Multicast_addr,sizeof(Multicast_addr));
		if(strcmp(buff,"QUIT")==0)
			break;
	}
	exit(0);

}

void * recvdata(void* arg){
	char buff[512];
	socklen_t len=sizeof(Multicast_addr);
	struct sockaddr_in temp;
	memcpy(&temp,&Multicast_addr,sizeof(Multicast_addr));
	while(1){
		bzero(buff,sizeof(buff));
		recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&temp,&len);
		printf("\33[2k\rRecieved: %s\nEnter: ",buff);
		fflush(stdout);
		if(strcmp(buff,"QUIT")==0)
			break;
	
	}
	exit(0);
}

void main(int argc,char ** argv){
	if(argc<3){
		printf("Provide Multicast IP and port number!\n");
		exit(1);
	}
	int res;
	
	Multicast_addr.sin_family=AF_INET;
	Multicast_addr.sin_port=htons(atoi(argv[2]));
	Multicast_addr.sin_addr.s_addr=inet_addr(argv[1]);

	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	int reuse=1;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
	res=bind(sockfd,(struct sockaddr*)&Multicast_addr,sizeof(Multicast_addr));
	if(res<0){
		perror("error ");
		exit(1);
	}

	struct ip_mreq mreq;

	mreq.imr_multiaddr.s_addr=inet_addr(argv[1]);
	mreq.imr_interface.s_addr=INADDR_ANY;

	res=setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
	if(res<0){
		perror("error ");
		exit(1);
	}
	
	pthread_t send_thread,recv_thread;
	pthread_create(&send_thread,NULL,senddata,NULL);
	pthread_create(&recv_thread,NULL,recvdata,NULL);
	pthread_exit(NULL);

}
