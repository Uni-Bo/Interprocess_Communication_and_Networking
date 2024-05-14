//MQ2

/*
struct buffer
{
	long msg_type;
	//The data you wish to transfer 
}

#include <sys/msg.h>

int msgget(key_t key, int msgflg);						    // used to get msqid(int), flag= 0666|IPC_CREAT

int msgctl(int msqid, int cmd, struct msqid_ds *buf);				    // used to control mq,we use IPC_RMID in place of cmd to terminate,flag=NULL

int msgrcv(int msqid, void *msg_ptr, size_t msg_sz, long int msgtype, int msgflg);  // used to recive message, flag=0

int msgsnd(int msqid, const void *msg_ptr, size_t msg_sz, int msgflg);              // used to send message, flag=0

*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define key 1357
typedef struct student
{
	char name[50];
	int roll;
}student;
typedef struct size
{
	long type;
	int n;
}size;
typedef struct message
{
	long type;
	student student;
}message;

