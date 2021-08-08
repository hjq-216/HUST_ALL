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
int count;
        printf("将共享内存中的内容输出到目标文件\n");
        //P(semid,1);
        FILE *fp=fopen(source,"r");
        fseek(fp,0,SEEK_END);
        long length=ftell(fp);
        fclose(fp);
        FILE *fp1;
        fp1=fopen(target,"w");
        buffer->out=0;
        for(count=0;count<length;count++){
            P(semid,1);
            printf("%c",buffer->buf[buffer->out]);
            fputc(buffer->buf[buffer->out],fp1);
            buffer->out++;
            buffer->out=buffer->out%BUFFSIZE;
            V(semid,0);
        }
        fclose(fp1);
shmdt(buffer);
        exit(0);
}
