#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

struct infobuf{
	long mtype;
	char name[128];
	int id[128];
	char personalinfo[128];
};

int main(void){
	struct infobuf info;
	char pname[128];
	int pid=0;
	memset(info.name,0,128); memset(info.id,0,128); memset(info.personalinfo,0,128);
	printf("please enter your NAME and ID \n");
	printf("Your NAME : ");
	scanf("%s",&pname);
	printf("Your ID : ");
	scanf("%d",&pid);

	sprintf(info.name,"%s",pname);
	sprintf(info.id,"%d",pid);
	strcat(info.personalinfo,info.name);
	strcat(info.personalinfo,info.id);
	key_t key;
	int msgid, msgiid;
	int fd1, fd2;
	ssize_t w1, w2;

	key=ftok("keyfile",1);
	msgid=msgget(key,IPC_CREAT|0644);

	if(msgid == -1){
	 perror("msgget");
	 exit(1);
	}
	info.mtype=1;
	if(msgsnd(msgid,(void*)&info,128,IPC_NOWAIT)==-1){
	 perror("msgsnd");
	 exit(1);
	}

	if((fd1=open(info.name, O_RDWR | O_CREAT,0644))<0)
	 return (-1);
	 w1 = write(fd1, info.personalinfo,strlen(info.personalinfo));
	
	int len;
	len = msgrcv(msgid, &info, 128,0,0);
	if((fd2=open(info.id, O_RDWR | O_CREAT,0644))<0)
	 return (-1);
	 w2 = write(fd2, info.personalinfo,strlen(info.personalinfo));
	
	return 0;
}

