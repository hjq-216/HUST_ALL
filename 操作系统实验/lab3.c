//
// Created by 黄俊淇的Mac on 2020/11/15.
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFSIZE 64
pid_t write_buf;
pid_t read_buf;

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
int main(void) {
    share_buffer = shmget(IPC_PRIVATE, sizeof(struct SHARE) , IPC_CREAT | 0666);
    buffer=(struct SHARE *)shmat(share_buffer,NULL,SHM_R|SHM_W);
    union semun arg;
    semid = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666); //创建write and read信号
    arg.val = BUFFSIZE;
    semctl(
            semid, 0, SETVAL,
            arg); // read进程设置信号灯大小为SIZE,当read到了SIZE大小时会阻塞,等待write使用
    arg.val = 0;
    semctl(semid, 1, SETVAL, arg); // write
    printf("%d\n",share_buffer);
    write_buf=fork();//将源文件内容写入共享内存
    if(write_buf==0){
        char write_id[20];
	char light_id1[20];
        sprintf(write_id,"%d",share_buffer);
	sprintf(light_id1,"%d",semid);
        printf("%d",share_buffer);
        printf("%s",write_id);
        char *arg1 = "./write";
        char *arg2 = write_id;
	char *arg3 = light_id1;
        char *arg4 = NULL;
	
        char *arg[] = {arg1, arg2, arg3,arg4};

        execv(arg[0], &arg[0]);
    }
    
    read_buf=fork();//将共享内存中的内容输出到目标文件
    if(read_buf==0){
        char read_id[20];
	char light_id2[20];
        sprintf(read_id,"%d",share_buffer);
	sprintf(light_id2,"%d",semid);
        char *arg1 = "./read";
        char *arg2 = read_id;
	char *arg3 = light_id2;
        char *arg4 = NULL;
        char *arg[] = {arg1, arg2, arg3,arg4};

        execv(arg[0], &arg[0]);

    }
    //父进程
    waitpid(write_buf, NULL, 0);
    waitpid(read_buf, NULL, 0);
    // remove semaphore
    semctl(semid, 1, IPC_RMID);
    // remove share memory
    shmctl(share_buffer, IPC_RMID, NULL);
    exit(0);

}


