#include "head.h"
#include <string.h>
#define MAX 20
void main()
{
	int msgid=msgget(key,0666|IPC_CREAT);
	int n,i;
	printf("Enter the number of Students");
	scanf("%d",&n);
	
	size size;
	size.n=n;
	
	size.type=10;
	msgsnd(msgid,(void*)&size,sizeof(size),0);
	
	/*size.type=11;
	msgsnd(msgid,(void*)&size,sizeof(size));*/
	
	message msg;
	msg.type=1;
	
	for(i=0;i<n;i++)
	{
		printf("Enter Name of student %d: ",i+1);
		scanf(" %s",msg.student.name);
		printf("Enter Roll no: ");
		scanf("%d",&msg.student.roll);
		msgsnd(msgid, (void*)&msg, sizeof(msg),0);
		bzero(msg.student.name,sizeof(msg.student.name));
	}
	
	
	
	
}
