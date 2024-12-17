#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int val;

int main() {
    pid_t pid, pid1;
    // fork a child process
    pid = fork();
    if(pid < 0) { // error occurred
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if(pid == 0) { // child process
        val = 1;
        pid1 = getpid();
        printf("child: val = %d\n", val); // A
        printf("child: *val = %d\n", &val); // B
    }
    else { // parent process
        val = -1;
        pid1 = getpid();
        printf("parent: val = %d\n", val);
        printf("parent: *val = %d\n", &val);
        wait(NULL);
    }
    val += 10;
    printf("bf rt val = %d\nbf rt *val = %d\n", val, &val);
    return 0;
}