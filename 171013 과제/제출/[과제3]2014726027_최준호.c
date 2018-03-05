#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(){
	char Id1[128], Id2[128], Id3[128], Id4[128], Id5[128];
	char Name1[128], Name2[128], Name3[128], Name4[128], Name5[128];
	char Firstinfo[128] = "First Student Info \n", Secondinfo[128] = "Second Student Info \n";
	char Thirdinfo[128] = "Third Student Info \n", Fourthinfo[128] = "Fourth Student Info \n";
	char Fifthinfo[128] = "Fifth Student Info \n";
	char firstid[128], secondid[128], thirdid[128], fourthid[128], fifthid[128];	
	char firstname[128], secondname[128], thirdname[128], fourthname[128], fifthname[128];
	char text1[128], text2[128], text3[128], text4[128], text5[128];
	char tt1[128], tt2[128], tt3[128], tt4[128], tt5[128];	

	memset(Id1,0,128); memset(Id2,0,128); memset(Id3,0,128); memset(Id4,0,128); memset(Id5,0,128);
	memset(Name1,0,128); memset(Name2,0,128); memset(Name3,0,128); memset(Name4,0,128); memset(Name5,0,128);
	memset(text1,0,128);(text2,0,128);(text3,0,128);(text4,0,128);(text5,0,128);
	memset(tt1,0,128);(tt2,0,128);(tt3,0,128);(tt4,0,128);(tt5,0,128);
	
	printf("Please put the students' id and name\n");
	printf("%s id : ",Firstinfo);
	scanf("%s", firstid);
	printf("name : ");
	scanf("%s", firstname);
	
	printf("\n%s id : ",Secondinfo);
        scanf("%s", secondid);
        printf("name : ");
        scanf("%s", secondname);

        printf("\n%s id : ",Thirdinfo);
        scanf("%s", thirdid);
        printf("name : ");
        scanf("%s", thirdname);

        printf("\n%s id : ",Fourthinfo);
        scanf("%s", fourthid);
        printf("name : ");
        scanf("%s", fourthname);

        printf("\n%s id : ",Fifthinfo);
        scanf("%s", fifthid);
        printf("name : ");
        scanf("%s", fifthname);

	sprintf(Id1, "%s", firstid); sprintf(Id2, "%s", secondid); sprintf(Id3, "%s", thirdid);
	sprintf(Id4, "%s", fourthid); sprintf(Id5, "%s", fifthid);
	sprintf(Name1,"%s",firstname); sprintf(Name2,"%s",secondname); sprintf(Name3,"%s",thirdname);
	sprintf(Name4,"%s",fourthname); sprintf(Name5,"%s",fifthname);
	int return_stat;
	mode_t file_mode;
	struct stat file_info;
	if((return_stat = stat("origin", &file_info)) == 0)
	{
	 exit(0);
	}
	file_mode = file_info.st_mode;
	if((S_ISDIR(file_mode)) == 0){
		if(mkdir("origin", 0755)){
			perror("Failed to make directory");
			return 1;
		}
	}
	if(chdir("origin")){
		perror("Failed to change directory");
		return 1;
	}
	int fd1, fd2, fd3, fd4, fd5;
	ssize_t w1, w2, w3, w4, w5;
	if((fd1 = open(Id1, O_RDWR | O_CREAT, 0644)) < 0)
		return (-1);
	w1 = write(fd1, Name1, 128);
	if((fd2 = open(Id2, O_RDWR | O_CREAT, 0644)) < 0)
		return (-1);
	w2 = write(fd2, Name2, 128);
	if((fd3 = open(Id3, O_RDWR | O_CREAT, 0644)) < 0)
                return (-1);
        w3 = write(fd3, Name3, 128);
        if((fd4 = open(Id4, O_RDWR | O_CREAT, 0644)) < 0)
                return (-1);
        w4 = write(fd4, Name4, 128);
        if((fd5 = open(Id5, O_RDWR | O_CREAT, 0644)) < 0)
                return (-1);
        w5 = write(fd5, Name5, 128);

        if(chdir("..")){
                perror("Failed to change directory");
                return 1;
        }

	if((return_stat = stat("copied", &file_info)) == 0)
        {
         exit(0);
        }
        file_mode = file_info.st_mode;
        if((S_ISDIR(file_mode)) == 0){
                if(mkdir("copied", 0755)){
                        perror("Failed to make directory");
                        return 1;
                }
        }

        if(chdir("origin")){
                perror("Failed to change directory");
                return 1;
        }

	int fdd1, fdd2, fdd3, fdd4, fdd5;
	ssize_t nread1, nread2, nread3, nread4, nread5;
	if((fdd1 = open(Id1, O_RDONLY)) < 0)
		return (-1);
	nread1 = read(fdd1, text1, 128);
	close(fdd1);
	if((fdd2 = open(Id2, O_RDONLY)) < 0)
		return (-1);
	nread2 = read(fdd2, text2, 128);
        close(fdd2);
	if((fdd3 = open(Id3, O_RDONLY)) < 0)
		return (-1);
	nread3 = read(fdd3, text3, 128);
        close(fdd3);
	if((fdd4 = open(Id4, O_RDONLY)) < 0)
		return (-1);
	nread4 = read(fdd4, text4, 128);
        close(fdd4);
	if((fdd5 = open(Id5, O_RDONLY)) < 0)
		return (-1);
	nread5 = read(fdd5, text5, 128);
        close(fdd5);
	
	if(chdir("..")){
                perror("Failed to change directory");
                return 1;
        }

	if(chdir("copied")){
                perror("Failed to change directory");
                return 1;
        }
	sprintf(tt1, "%s", text1);
	sprintf(tt2, "%s", text2);
	sprintf(tt3, "%s", text3);
	sprintf(tt4, "%s", text4);
	sprintf(tt5, "%s", text5);

	int fd11, fd22, fd33, fd44, fd55;

	if((fd11 = open(Id1, O_RDWR | O_CREAT, 0644)) < 0)
                return (-1);
        w1 = write(fd11, tt1, 128);
        if((fd22 = open(Id2, O_RDWR | O_CREAT, 0644)) < 0)
                return (-1);
        w2 = write(fd22, tt2, 128);
        if((fd33 = open(Id3, O_RDWR | O_CREAT, 0644)) < 0)
                return (-1);
        w3 = write(fd33, tt3, 128);
        if((fd44 = open(Id4, O_RDWR | O_CREAT, 0644)) < 0)
                return (-1);
        w4 = write(fd44, tt4, 128);
        if((fd55 = open(Id5, O_RDWR | O_CREAT, 0644)) < 0)
                return (-1);
        w5 = write(fd55, tt5, 128);	
	
	return 0;
}
	
