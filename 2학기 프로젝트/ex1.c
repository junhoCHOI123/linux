#include <signal.h>
#include <stdlib.h>
#include <termio.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/types.h>

#define EOL             1              
#define THING             2              
#define AMPERSAND       3               
#define SEMICOLON       4               
#define PIPE            5               
#define INREDI			6	
#define OUTREDI			7
#define TAP				8		

#define FALSE           0               
#define TRUE            1               

#define FORE_G      	0               
#define BACK_G      	1              

char* shellline = "junho shell> ";

char in_buf[1024], tok_buf[2048], *ptr = in_buf, *tok = tok_buf;

char specific [] = { ' ', '\t', '&', '|', ';', '<', '>', '\n','\0' };		//특별 기호들을 지정해줌.
char end = 'q';

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


int main()
{
	act.sa_handler = SIG_IGN;
	sigfillset(&(act.sa_mask));
	sigaction(SIGINT, &act, NULL);
	
	while(putin(shellline) != 'q')
		dosome();

	return 0;
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

	while(1)
	{
		if( (c=getchar() ) == 'q' )		
			exit(0);

		if (count < 1024)				
			in_buf[count++] = c;

		if( c== '\n' && count < 1024 )	
		{
			in_buf[count] = '\0';
			return count;
		}

		if(c == '\n')
		{
			printf("It's too long\n");
			count = 0;
			printf("%s",com);
		}

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
	}
	
}

int gettok( char** outptr)
{
	int type;

	*outptr = tok;

	while( *ptr ==' ' || *ptr == '\t')
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
	char* wrk;

	for(wrk = specific; *wrk; wrk++)
	{
		if( c == *wrk)	
			return 0;
	}
	return 1;
}


int dosome(void)	
{
	char* arg[2049];		
	int toktype;				
	int narg;					
	int type;					
	int pipe=FALSE;				
	int pipething;				
	int i;

	narg = 0;			

	for(;;)		
	{
		switch( toktype = gettok(&arg[narg]))
		{
			case THING :			
				if(narg < 1024 )
					narg++;
				break;
			
			case PIPE :			
				pipe = TRUE;		
				pipething = narg;	
				if(narg < 1024 )	
					narg++;		
				break;

			case EOL:			
			case SEMICOLON :	
			case AMPERSAND:		
				if(toktype == AMPERSAND )
					type = BACK_G;
				else
					type = FORE_G;

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

	switch( pid = fork() )	
	{
		case -1 :	
			perror("smallsh");
			return (-1);

		case 0 :	
			act.sa_handler = SIG_DFL;
			sigfillset(&(act.sa_mask));
			sigaction(SIGINT, &act, NULL);

			if(pipe == TRUE)	
			{
				gogogo[pipething] = NULL;
				letspipe(gogogo, (gogogo+(pipething+1) ) );
				exit(1);				
			}

			execvp(*gogogo,gogogo);
			perror(*gogogo);
			exit (1);
	}
	
	
	if(where == BACK_G)
	{
		printf("[Process id %d]\n",pid);
		return (0);
	}

	if(waitpid(pid, &status, 0) == -1)
		return (-1);
	else 
		return (status);
}


int letspipe(char* pipe1[], char* pipe2[] )
{
	int p[2], status;

	switch(fork())
	{
		case -1 :		
			perror("fork is not succeed");

		case 0 :		
			break;

		default :		
			wait(&status);
			return (status);
	}

	if(pipe(p) == -1)
		perror("pipe error");
	switch(fork())
	{
		case -1 :			
			perror("fork is not succeed");
		
		case 0 :				
			dup2(p[1],1);
			execvp(pipe1[0], pipe1);
			perror("execvp is not succeed");

		default :				
			dup2(p[0], 0);
			execvp(pipe2[0],pipe2);	
			perror("execvp is not succeed");
	}
}
