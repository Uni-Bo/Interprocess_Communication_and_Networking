#include "head.h"
#include <string.h>
#define MAX 20
void main()
{
	int msgid=msgget(key,0666|IPC_CREAT);
	int n,i;
	size size;
	
	msgrcv(msgid,(void*)&size, sizeof(size),10,0);
	n=size.n;
	
	message msg;
	student *student=malloc(sizeof(student)*n);
	
	for(i=0;i<n;i++)
	{
		msgrcv(msgid, (void*)&msg, sizeof(msg),1,0);
		
		strcpy(student[i].name,msg.student.name);
		
		student[i].roll=msg.student.roll;
		
		printf("Recived: Name of student %d: %s, Roll no: %d\n",i+1, student[i].name, student[i].roll);
		
		bzero(msg.student.name, sizeof(msg.student.name));
	}
	
}
