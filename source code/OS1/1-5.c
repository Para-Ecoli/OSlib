#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid, pid1;
    // fork a child process
    pid = fork();
    if(pid < 0) { // error occurred
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if(pid == 0) { // child process
        pid1 = getpid();
        printf("child process: PID: %d\n", pid1);

        // system()
        // printf("system(): ");
        system("./system_call");

        printf("child process: PID: %d\n", pid1);

        // exec
        // printf("exec: ");
        char *args[] = {"./system_call", NULL};
        execvp(args[0], args);

        printf("child process: PID: %d\n", pid1);
    }
    else { // parent process
        pid1 = getpid();
        printf("parent process PID %d\n", pid1);
        printf("child process PID %d\n", pid);
        wait(NULL);
    }
    return 0;
}