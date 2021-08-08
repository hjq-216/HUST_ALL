#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


// set p1, p2 and pipe_id as global to make sure `my_func` have access to them when called
int p1;
int p2;
int pipefd1[2];
int pipefd2[2];

// SIGINT signal handler for parent process
void my_func(int signum) {
    signal(SIGINT, SIG_DFL);
    kill(p1, SIGTERM);
    waitpid(p1, NULL, 0);
    kill(p2, SIGTERM);
    waitpid(p2, NULL, 0);
    close(pipefd1[0]);
    close(pipefd1[1]);
    close(pipefd2[0]);
    close(pipefd2[1]);
    printf("Parent Process is Killed\n");
    exit(EXIT_SUCCESS);
}

void p1_killed() {
    printf("Child Process 1 is Killed by Parent!\n");
    exit(EXIT_SUCCESS);
}

void p2_killed() {
    printf("Child Process 2 is Killed by Parent!\n");
    exit(EXIT_SUCCESS);
}

int main() {
    // Ctrl + C will emit SIGINT signal
    char buffer[BUFSIZ];
    pipe(pipefd1);
    pipe(pipefd2);
    signal(SIGINT, my_func);
    p1 = fork();
    if(p1>0){
        p2 = fork();
        if (p2 == 0) {
            // Child 2 process
            signal(SIGINT, SIG_IGN);
            signal(SIGTERM, p2_killed);
            while(1) {
                read(pipefd2[0], buffer, BUFSIZ);
                printf("%s", buffer);

            }
        }
        else{
            int x=1;
            while(1) {
                sprintf(buffer, "I send you %d times\n", x);
                x++;
                write(pipefd1[1], buffer, BUFSIZ);
                write(pipefd2[1], buffer, BUFSIZ);
                if(x==10){
                    sleep(1);
                    kill(p1, SIGTERM);
                    waitpid(p1, NULL, 0);
                    kill(p2, SIGTERM);

                    waitpid(p2, NULL, 0);
                    close(pipefd1[0]);
                    close(pipefd1[1]);
                    close(pipefd2[0]);
                    close(pipefd2[1]);
                    printf("Parent Process is Killed\n");
                    break;
                }
                sleep(1);
            }

            return 0;
        }
    }
    else if (p1 == 0) {
        // Child 1 process
        signal(SIGINT, SIG_IGN);
        signal(SIGTERM, p1_killed);
        while(1) {
            read(pipefd1[0], buffer, BUFSIZ);
            printf("%s", buffer);
        }
    }

}

