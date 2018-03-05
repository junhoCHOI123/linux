//2014726027 CHOI
#include <sys/sem.h>
#include <sys/shm.h>

#define READ_KEY 7982
#define WRITE_KEY 7983
#define SHM_KEY 7984
#define SHM_SIZE 100

void p(int semid);
void v(int semid);

