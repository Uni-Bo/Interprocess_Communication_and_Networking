#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

void verify(char* ip,int * res){
	struct sockaddr_in temp;
	*res=inet_pton(AF_INET,ip,&temp.sin_addr);
}

void main(int argc,char ** argv){
	if(argc<2){
		printf("Error! provide port number.\n");
		exit(1);
	}
	
	struct sockaddr_in server,client[50];
	int client_num=0;
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[1]));
	server.sin_addr.s_addr=INADDR_ANY;
	
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	int res=bind(sockfd,(struct sockaddr*) &server,sizeof(server));
	if(res!=0){
		perror("Error ");
		exit(1);
	}
	
	listen(sockfd,1);

	while(1){
		socklen_t len=sizeof(client[client_num]);
		pid_t id=fork();
		char ip[256];
		bzero(ip,sizeof(ip));
		if(id==0){
			int newfd=accept(sockfd,(struct sockaddr*)&client[client_num++],&len);
			read(newfd,ip,sizeof(ip));
			printf("\nRecieved: %s\n",ip);
			int res;
			verify(ip,&res);
			bzero(ip,sizeof(ip));
			if(res==1){
				strcpy(ip,"YES");
				write(newfd,ip,sizeof(ip));
			}else{
				strcpy(ip,"NO");
				write(newfd,ip,sizeof(ip));
			}
		}
	}
	
}
