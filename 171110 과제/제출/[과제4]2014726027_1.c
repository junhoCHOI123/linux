#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#define BUFSIZE 10

int main(void){
	char putname[128], name[128], sonid[128], sonname[128];
	char id[128];
	int putid=0;
	char personalinfo[128];

	memset(id, 0, 128); memset(name,0,128); memset(personalinfo,0,128);
	memset(sonid,0,128); memset(sonname,0,128);

	printf("Please put the your NAME and ID\n");
	printf("ID : ");
	scanf("%d",&putid);
	printf("NAME : ");
	scanf("%s",&putname);

	sprintf(id, "%d", putid);
	sprintf(name, "%s", putname);
	strcat(personalinfo, id);
	strcat(personalinfo, name);

	int bytesin1 = strlen(id);
	int bytesin2 = strlen(name);
	int bytesin3 = strlen(personalinfo);
	pid_t childpid;
	int fd[2];

	if(pipe(fd) == -1){
	 perror("Failed to create the pipe");
	 return 1;
	}

	int fd1, fd2;
	ssize_t w1, w2;
	childpid=fork();
	if(childpid==-1){
	 perror("Failed to fork");
	 exit(1);
	}

	if(childpid){
	 write(fd[0],id, strlen(id));
	 write(fd[0],name, strlen(name));
	 write(fd[0],personalinfo,strlen(personalinfo));
	 if((fd1 = open(name,O_RDWR | O_CREAT, 0644))<0)
	   return (-1);
	 w1 = write(fd1, personalinfo, strlen(personalinfo));
	 return 1;
	}

	else{
	 bytesin1 = read(fd[1],id, strlen(id));
	 bytesin2 = read(fd[1],name,strlen(name));
	 bytesin3 = read(fd[1],personalinfo,strlen(personalinfo));
	 if((fd2 = open(id, O_RDWR | O_CREAT, 0644))<0)
	   return (-1);
	  w2 = write(fd2, personalinfo, strlen(personalinfo));
	 return 1;	
	 }
	return 0;
}
