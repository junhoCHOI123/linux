#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>

#define KEY 14726027
#define PERM 0660

pthread_mutex_t mutx;
pthread_t t1;

void *thread_increment(void *arg);

struct info{
int id;
char name[32];
};

struct info stuinfo[10];


int main(int argc, char **argv){

	int state;
	int shmid;
	char *memptr;
	void *thread_result;
	int i;
	
	state = pthread_mutex_init(&mutx, NULL);
	if(state){
		puts("Failed to init mutex");
		exit(1);
	}

	if((shmid = shmget(KEY, 100, PERM|IPC_CREAT))<0){
		perror("shmget");
		exit(1);
	}
	
	if((memptr = shmat(shmid, (char *)0, 0)) == (char *)(-1)){
		perror("shmat error");
		exit(1);
	}

		
	pthread_create(&t1, NULL, thread_increment, stuinfo);	
	pthread_join(t1, &thread_result);
	
	for(i=0 ; i<10 ; i++){
		printf("[%d] %s \n",stuinfo[i].id, stuinfo[i].name);
	}

	pthread_mutex_destroy(&mutx);
	
	if(shmdt(memptr)<0){
		perror("shmdt");
		exit(1);
	}

	return 0;
}

void *thread_increment(void *arg){

	int i;
	char new1[32], new2[32];
	char a[32] = "student";

	for(i=0 ; i<10 ; i++){
		sprintf(new2,"%d",i);
		strcat(new1,a);
		strcat(new1,new2);

		pthread_mutex_lock(&mutx);

		stuinfo[i].id = i;
		memcpy(stuinfo[i].name,new1,32);
		memset(new1,0,32);

		pthread_mutex_unlock(&mutx);
	}
}
