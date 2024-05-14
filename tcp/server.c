#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

void bit_stuff(const char*msg, char* res)
{
	int c=0,i=0,j=0;
	while(msg[i]!='\0')
	{
		if(c==5)
		{
			res[j++]='0';
			c=0;
		}
		if(msg[i]=='0')
		{
			res[j++]='0';
			c=0;
		}
		else
		{
			res[j++]=msg[i];
			c++;
		}
		i++;
	}
	if(c==5)
		res[j++]='0';
}

int main()
{
	int server_sockfd, client_sockfd;
	socklen_t server_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	
	char stream[1024],res[1024];

	if((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		handle_error("socket");

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_port = 8086;
	server_len = sizeof(server_address);
	
	if(bind(server_sockfd, (struct sockaddr*)&server_address, sizeof(server_address))==-1)
		handle_error("bind");
	
	if(listen(server_sockfd,5)==-1)
		handle_error("listen");
	
	socklen_t client_len=sizeof(client_address);
	printf("Waiting..\n");
	client_sockfd=accept(server_sockfd, (struct sockaddr*)&client_address, &client_len);
	 if (client_sockfd == -1)
               handle_error("accept");
        printf("ACCEPTED\n");   
	
	memset(stream,'\0',sizeof(stream));
	
	recv(client_sockfd,stream,sizeof(stream),0);
	
	printf("Recived: %s\n",stream);
	
	memset(res,'\0',sizeof(res));
	bit_stuff(stream,res);

	write(client_sockfd,res,strlen(res));
	
	close(server_sockfd);
	close(client_sockfd);
	
	return 0;
}

