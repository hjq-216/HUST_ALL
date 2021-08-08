#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFSIZE 64

union semun {
    int val;               /* value for SETVAL */
    struct semid_ds *buf;  /* buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* array for GETALL, SETALL */
    struct seminfo *__buf; /* buffer for IPC_INFO */
};
void P(int semid, int index) {
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
    return;
}
void V(int semid, int index) {
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
    return;
}
struct SHARE{
    char buf[BUFFSIZE];
    int in,out;
};

int share_buffer;
int semid;
const char * source = "/home/parallels/Desktop/exp3/input.txt";
const char * target = "/home/parallels/Desktop/exp3/output.txt";
struct SHARE *buffer;
int main(int argc, char *argv[]){

share_buffer=atoi(argv[1]);
semid=atoi(argv[2]);
    buffer=(struct SHARE *)shmat(share_buffer,NULL,SHM_R|SHM_W);
FILE *fp=fopen(source,"r");
        int count;
        printf("将源文件内容写入共享内存\n");
        fseek(fp,0,SEEK_END);
        long length=ftell(fp);
        fseek(fp,0,SEEK_SET);
        buffer->in=0;
        for(count=0;count<length;count++){
            P(semid,0);

            buffer->buf[buffer->in]=fgetc(fp);
            printf("%c",buffer->buf[buffer->in]);
            buffer->in++;
            buffer->in%=BUFFSIZE;
            V(semid,1);
        }
        fclose(fp);
shmdt(buffer);
        exit(0);
}
