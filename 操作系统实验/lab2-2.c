#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
int a = 0;
int semid;
int count=0;

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO */
};
void P(int semid, int index) {
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = SEM_UNDO;
    semop(semid, &sem, 1);
    return ;
}

void V(int semid, int index) {
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = 1;
    sem.sem_flg = SEM_UNDO;
    semop(semid, &sem, 1);
    return ;
}


void * subp1() {
    while(1) {
	
        P(semid, 0);
	if(a==5050) {
	if(count==0) printf("1: Calculation: %d\n",a);	
	V(semid, 1);
	break;
	}
        if(a%2==0){
            if(count) count=0;
            //P(semid,2);
            if(count==0) printf("1: Calculation: %d\n",a);

            //V(semid,2);
            V(semid, 1);
            //if(a==4851) break;
        }
        else{
            count++;
            V(semid, 0);
            //if(a==5050) break;
            //V(semid,2);
        }

    }
}
void * subp2() {
    while(1) {
	
        P(semid, 0);
	if(a==4851) {
	printf("2: Calculation: %d\n",a);
	V(semid, 1);
	break;
	}
        if(a%2){
            if(count) count=0;
            //P(semid,2);
            if(count==0) printf("2: Calculation: %d\n",a);

            //V(semid,2);
            V(semid, 1);
            //if(a==5050) break;
        } else{
            count++;
            V(semid, 0);
            //if(a==5050) break;
            //V(semid,2);
        }

    }
}

void * subp3() {
    for (int i = 1; i <= 100; i++) {
        P(semid, 1);
        a += i;
        V(semid, 0);
    }
}

int main(void) {
    // int semid;
    struct sembuf sembuf;

    if ((semid = semget(IPC_PRIVATE, 0, 0)) == -1) {
        // 如果信号灯集不存在的话，就创建两个信号灯
        if ((semid = semget(IPC_PRIVATE, 3, IPC_CREAT | 0666)) != -1) {
            // 如果创建成功
            union semun arg0;
            union semun arg1;
            union semun arg2;
            arg0.val = 1;
            arg1.val = 0;
            arg2.val=1;
            // 设置信号灯的量分别为0,1
            if (semctl(semid, 1, SETVAL, arg1) == -1 || semctl(semid, 0, SETVAL, arg0) == -1) {
                perror("IPC error 1: semctl");
                exit(1);
            }
            pthread_t p1;
            pthread_t p2;
            pthread_t p3;
            // 创建线程p1, p2
            pthread_create(&p1, NULL, subp1, NULL);
            pthread_create(&p2, NULL, subp2, NULL);
            pthread_create(&p3, NULL, subp3, NULL);
            pthread_join(p1, NULL);
            pthread_join(p2, NULL);
            pthread_join(p3, NULL);
            // 销毁信号灯
            if (semctl(semid, 0, IPC_RMID) == -1) {
                perror("Destroy Semaphore Failed!\n");
            }

        } else {
            perror("IPC error 2: semget");
            exit(1);
        }
    } else {
        perror("Semaphore is allready created!");
        exit(1);
    }
    return 0;
}

