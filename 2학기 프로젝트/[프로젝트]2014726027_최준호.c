#include <signal.h>
#include <stdlib.h>
#include <termio.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/types.h>

#define EOL             1              
#define THING           2              
#define AMPERSAND       3               
#define SEMICOLON       4               
#define PIPE            5               
#define INREDI		6		
#define OUTREDI		7
#define TAP		8	  

char in_buf[1024];
char tok_buf[2048];
char *ptr = in_buf;
char *tok = tok_buf;

char specific [] = { ' ', '\t', '&', '|', ';', '<', '>', '\n','\0' };
char end = 'q';
char* prompt = "junho shell> ";

int putin(char *com);					
int gettok( char** outptr);				
int inthing(char c);						
int dosome(void);						
int runcommand(char** gogogo, int where, int pipe, int pipething);						
void catchint(int signo);			
int letspipe(char* pipe1[], char* pipe2[] );

static struct sigaction act;				

int getch(void){
        int ch;
        struct termios buf, save;
        tcgetattr(0,&save);
        buf = save;
        buf.c_lflag &= ~(ICANON | ECHO);
        buf.c_cc[VMIN] = 1;
        buf.c_cc[VTIME] = 0;
        tcsetattr(0, TCSAFLUSH, &buf);
        ch = getchar();
        tcsetattr(0,TCSAFLUSH,&save);
        return ch;
}

int putin(char *com)
{
	int c, count;
	char get[5];
	ptr = in_buf;
	tok = tok_buf;
	DIR *dp;
	struct dirent *dirp;
	printf("%s", com);

	count = 0;		

	for(;;)
	{
		if( (c=getchar() ) == end )		
			exit(0);

		if( c== "ls")
		{
			dp = opendir(".");
			while(dirp=readdir(dp))
			{
				printf("%s ", dirp->d_name);
			}
			puts(" ");
			closedir(dirp);
		}
		
		if (count < 1024)				
			in_buf[count++] = c;

		if( c== '\n' && count < 1024 )	
		{
			in_buf[count] = '\0';
			return count;
		}
	}
}

int gettok( char** outptr)
{
	int type;

	*outptr = tok;

	if( *ptr ==' ')
		ptr++;

	*tok++ = *ptr;

	switch(*ptr++)
	{
	case '\n'  :	
		type = EOL;		
		break;

	case '&' :		
		type = AMPERSAND;
		break;

	case ';' :		
		type = SEMICOLON;
		break;

	case '|' :		
		type = PIPE;
		break;

	case '>' :
		type = INREDI;
		break;

	case '<' :
		type = OUTREDI;
		break;

	case '\t' :
		type = TAP;
		break;

	default :
		type = THING;
		
		while(inthing(*ptr) )
			*tok++ = *ptr++;
	}
	
	*tok++ ='\0';
	return type;
}


int inthing(char c)
{
	char* dodo;

	for(dodo = specific; *dodo; dodo++)
	{
		if( c == *dodo)	
			return 0;
	}
	return 1;
}


int dosome()	
{
	char* arg[2049];		
	int toktype;				
	int narg;					
	int type;					
	int pipe=0;				
	int pipething;				
	int i;

	narg = 0;			

	while(1)		
	{
		switch( toktype = gettok(&arg[narg]))
		{
			case THING :			
				if(narg < 1024 )
					narg++;
				break;
			
			case PIPE :			
				pipe = 1;		
				pipething = narg;	
				if(narg < 1024 )	
					narg++;		
				break;

			case EOL:			
			case SEMICOLON :	
			case AMPERSAND :		
				if(toktype == AMPERSAND )
					type = 1;
				else
					type = 0;

				if (narg != 0 )		
				{
					arg[narg] = NULL;
					runcommand(arg, type, pipe, pipething);
				}

				if(toktype == EOL)
					return 0;

				narg = 0;
				break;
			
			case INREDI :
				break; 
			case OUTREDI :
				break; 
			case TAP :
				break;

		}
	}
}


int runcommand(char** gogogo, int where, int pipe, int pipething)
{
	pid_t pid;
	int status;

	pid = fork();

	if(pid == -1)
		printf("Failed to fork");

	if(pid == 0){
		if(pipe == 1)
		{
			gogogo[pipething]=NULL;
			letspipe(gogogo, (gogogo+(pipething+1)));
			exit(1);
		}
		execvp(*gogogo, gogogo);
		exit(1);
	}
	
	if(where == 1)
		return 0;

	if(waitpid(pid, &status, 0) == -1)
		return (-1);

	else 
		return status;
}


int letspipe(char* pipe1[], char* pipe2[] )
{
	int todup[2], status;
	pid_t pid1,pid2;

	pid1 = fork();

	if(pid1 == -1)
		printf("fork is not succeed");
	else if(pid1 == 0);
	else
	{
		wait(&status);
		return status;
	}

	if(pipe(todup) == -1)
		printf("Fife error");

	pid2=fork();

	if(pid2 ==- 1)
		printf("fork is not succeed");
	else if(pid2 == 0)
	{
		dup2(todup[1],1);
		execvp(pipe1[0], pipe1);
	}
	else
	{
		dup2(todup[0], 0);
		execvp(pipe2[0],pipe2);
	}
}

int main()
{
	act.sa_handler = SIG_IGN;
	sigfillset(&(act.sa_mask));
	sigaction(SIGINT, &act, NULL);
	
	while(1)
	{
		if(putin(prompt) != end)
		dosome();
	}
	return 0;
}
