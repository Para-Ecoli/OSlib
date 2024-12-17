#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

pid_t pid1 = -1, pid2 = -1;

void parent_handler(int sig) {
    printf("\n%d stop test\n", sig);
    printf("16 stop test\n");
    while(kill(pid1, 16) < 0);
    printf("17 stop test\n");
    while(kill(pid2, 17) < 0);
}

void child_handler(int sig) {
    if(sig == 16) {
        printf("\nchild process 1 (pid = %d ) is killed by signal %d\n", getpid (), sig);
    }
    if(sig == 17) {
        printf("\nchild process 2 (pid = %d ) is killed by signal %d\n", getpid (), sig);
    }
    exit(0);
}

int main() {

    while (pid1 == -1) pid1 = fork(); //尝试创建子进程 1
    if (pid1 > 0) {
        while (pid2 == -1) pid2 = fork(); //尝试创建子进程 2
        if (pid2 > 0) {
            // TODO: 父进程
            printf("parent process (pid=%d) now waiting sigal in five seconds\n", getpid ());
            signal(SIGINT, parent_handler);
            signal(SIGQUIT, parent_handler);
            signal(SIGALRM, parent_handler);
            alarm(5);
            wait(NULL);
            wait(NULL);
            printf("\nParent process is killed!!\n");
        }
        else {
            // TODO: 子进程 2
            signal(SIGINT, SIG_IGN);
            signal(SIGQUIT, SIG_IGN);
            signal(17, child_handler);
            pause();
        }
    }
    else {
        // TODO: 子进程 1
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        signal(16, child_handler);
        pause();
    }

    return 0;
}