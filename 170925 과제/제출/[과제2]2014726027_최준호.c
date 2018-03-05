#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void){
int month=0, day=0, time=0;
int fd, status, spid;
char monthc[50], dayc[50], timec[50];
ssize_t w1, w2;
char goinson[10], goinparent[10], goinacc[20], goinmod[20];
char thisone[30]="Child Process ID : ",  thistwo[30] = "\n Parent Process ID : ";
char thisthree[40]="Last access time : ", thisfour[40] = "\n Last Modified time : ";

memset(monthc,0,50);
memset(dayc,0,50);
memset(timec,0,50);
memset(goinson,0,10);
memset(goinparent,0,10);

printf("Please enter month, day and time\n");
scanf("%d %d %d",&month, &day, &time);

sprintf(monthc, "%d", month);
sprintf(dayc, "%d", day);
sprintf(timec, "%d", time);

if(mkdir(monthc, 0755)){
	perror("Failed to make directory");
	return 1;
}

if(chdir(monthc)){
	perror("Failed to change directory");
	return 1;
}

if(((creat(dayc, 0755))<0) || (creat("Record_Time", 0755))<0){
        printf("Failed to make files");
        return 1;
}

pid_t pid;
pid=fork();

if(pid==-1){
	printf("Failed to fork");
	exit(1);
}

else if(pid==0){
	sleep(time);
	printf("I will be back %d \n",getpid());

	sprintf(goinson,"%d",getpid());
	sprintf(goinparent,"%d",getppid());
	strcat(thisone, goinson);
	strcat(thistwo, goinparent);	


	if((fd = open(dayc, O_RDWR | O_APPEND, 0644))>=0){

        write(fd,thisone,strlen(thisone));
	write(fd,thistwo,strlen(thistwo));

        close(fd);
	}
	else{
        printf("Failed to open file");
	}

	return 1;
}

else{
	spid = wait(&status);
	int return_stat;
	struct stat file_info;
	if ((return_stat = stat(dayc, &file_info))==-1)
	{
		perror("Error: ");
		exit(0);
	}
	sprintf(goinacc, "%d", (int)file_info.st_atime);
	sprintf(goinmod, "%d", (int)file_info.st_mtime);
	strcat(thisthree, goinacc);
	strcat(thisfour, goinmod);

	if((fd = open("Record_Time", O_RDWR | O_APPEND, 0644))>=0){
	
	write(fd, thisthree,strlen(thisthree));
	write(fd, thisfour,strlen(thisfour));
	close(fd);
	}
	else{
	printf("Failed to open file");
	}
	return 1;
}

return 0;
}
