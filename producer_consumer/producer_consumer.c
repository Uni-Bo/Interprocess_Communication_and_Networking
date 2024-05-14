#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include "buffer.h"

sem_t mutex, full, empty;

void * producer (void * arg)
{
	int i=0;
	buffer* buffer= arg;
	
	while(1)
	{	
		sem_wait(&empty);
		sem_wait(&mutex);
	
		push(buffer,i);
		i++;
		printf("\nProduced: %d",i);
	
		sem_post(&mutex);
		sem_post(&full);

	}
}

void * consumer (void * arg)
{
	int i=0;
	buffer* buffer= arg;
	
	while(1)
	{	
		sleep(1);
		sem_wait(&full);
		sem_wait(&mutex);
	
		i=pop(buffer);
		printf("\nConsumed: %d",i);
	
		sem_post(&mutex);
		sem_post(&empty);

	}
}


void main()
{
	sem_init(&mutex,0,1);
	sem_init(&full,0,0);
	sem_init(&empty,0,5);
	
	pthread_t produce, consume;
	
	buffer buffer;
	buff_init(&buffer);
	
	pthread_create(&produce,NULL,producer,(void*)&buffer);
	pthread_create(&consume,NULL,consumer,(void*)&buffer);
	
	pthread_join(produce,NULL);
	pthread_join(consume,NULL);
	
	sem_destroy(&mutex);
}
	
	
	
