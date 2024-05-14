#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
int p;

void * check_prime(void * arg){
	int i,j;
	int start=*(int*)arg;
	int flag;
	if(start<2)
		start=2;
		
	//printf(" \n Start: %d",start);
	
	for(i=start;i<start+10;i++){
		flag=1;
		for(j=2;j<i;j++){
			if(i%j==0){
				flag=0;
				break;
			}
		}
		
		if(flag)
			printf("\n %d is prime ",i);
		
	}
	
	
	p=rand()%100;
	pthread_exit((void *) &p);
	
	//return (void *) &p;
	
}

void main(){

	srand(time(NULL));
	pthread_t th[10];
	int x=0;
	int * d;
	for(int i=0;i<10;i++){
		d=malloc(sizeof(int));
		*d=x;
		x+=10;
		pthread_create(&th[i],NULL,check_prime,d);
	}
	
	int *ptr;
	
	for(int i=0;i<10;i++){
		pthread_join(th[i],(void**)&ptr);
		printf(" \nReturned %d",*ptr);
		}
		
	//pthread_exit(NULL);
	
}
