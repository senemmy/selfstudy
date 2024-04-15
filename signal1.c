#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
    int pid = fork();

    if(pid == -1) {
        printf("err while creating child process...\n");
        return 1;
    } else if(pid == 0) {
        while(1) {
            printf("working in child process...\n");
            usleep(50000);
        }
    } else {
        int var;
        kill(pid, SIGSTOP);

        do{
            printf("Time for wating to child process working...\n");
            scanf("%d", &var);
            printf("*********************************\n");
            if(var > 0) {
                kill(pid, SIGCONT);
                sleep(var); // child process is running for var sec
                kill(pid, SIGSTOP);
            }
        } while(var > 1);

        kill(pid, SIGKILL);
        wait(NULL);
    }



    return 0;
}