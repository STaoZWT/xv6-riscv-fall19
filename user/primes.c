#include "kernel/types.h"
#include "user/user.h"
/*
    Edited by Wentao Zhang 
    2020/10/27
*/

int main(int argc, char *argv[]) {
    int fd[2];
    int received;
    int result = pipe(fd);
    if (result == -1) {
        printf("create pipe error!\n");
        return -1;
    }
    for (int i = 2; i < 35; i++) {
        result = write(fd[1], &i, sizeof(int));
    }
    close(fd[1]);
    int pid;
    pid  = fork();
    if (pid == 0) {
        
    } else {
        
    }

}



// int main(int argc, char *argv[]) {
//     int fd[2];
//     int received;
//     int result = pipe(fd);
//     if (result == -1) {
//         printf("create pipe error!\n");
//         return -1;
//     }

//     int pid;
//     int i = 2;
//     // for(;;) {
        
//         pid = fork();
//         if (pid > 0) {
//             close(fd[0]);
//             result = write(fd[1], &i, sizeof(int));
//             close(fd[1]);

//             exit();

//         } else {
//             close(fd[1]);
//             read(fd[0], &received, sizeof(received));
//             close(fd[0]);
//             for (int j = received + 1; j <= 35; j++)
//             {
//                 if (j % received != 0) {
//                     printf("output %d\n", j);
//                 }
//             }
//             exit();
//         }
//     // }
//     return 0;
// }