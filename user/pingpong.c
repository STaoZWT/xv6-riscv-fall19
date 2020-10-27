#include "kernel/types.h"
#include "user/user.h"
/*
    Edited by Wentao Zhang 
    2020/10/27
*/
int main(int argc, char *argv[]) {

    int parent_fd[2];
    
    int child_fd[2];
    
    char buf1[5];
    char buf2[5];
    // int n1;
    // int n2;

    int result1 = pipe(parent_fd);
    int result2 = pipe(child_fd);

    if (result1 == -1) {
        printf("create pipe1 error!\n");
        return -1;
    }

    if (result2 == -1) {
        printf("create pipe2 error!\n");
        return -1;
    }



    int pid = fork();
    if (pid > 0) { 
        /* Parent process */
        //printf("parent process %d\n", getpid());
        close(parent_fd[0]);
        result1 = write(parent_fd[1], "ping", 4);
        close(parent_fd[1]);

        close(child_fd[1]);
        read(child_fd[0], buf2, sizeof(buf2));
        printf("%d: received %s\n", getpid(), buf2);
        close(child_fd[1]);

        exit();        

    } else if (pid == 0) {
        /* Child process */
        //printf("child process %d\n", getpid());
        close(parent_fd[1]);
        read(parent_fd[0], buf1, sizeof(buf1));
        printf("%d: received %s\n", getpid(), buf1);
        close(parent_fd[0]);

        close(child_fd[0]);
        result2 = write(child_fd[1], "pong", 4);
        close(child_fd[1]);

        exit();
    
    } else {
        /* Handle errors */
        printf("Fork error!\n");
    }
    return 0;
}