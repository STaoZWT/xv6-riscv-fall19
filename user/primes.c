#include "kernel/types.h"
#include "user/user.h"
/*
    Edited by Wentao Zhang 
    2020/10/27
*/


// void recursive(int input_port) {
//     int first_value;
//     int other_value;
    
//     //output first received number (must be prime)
//     int read_result = read(input_port, &first_value, sizeof(int));
//     if (read_result > 0) {
//         printf("prime %d\n", first_value);
//     } else {
//         exit();
//     }

//     //create new pipe
//     int new_pipe[2];
//     int result = pipe(new_pipe);
//     if (result == -1) {
//         printf("create pipe error!\n");
//         exit();
//     }

//     //pass value to next pipe
//     int pid = fork();
//     if (pid == 0) {
//         //child: pass other values from input port to new pipe recursively
//         close(new_pipe[1]);
//         recursive(new_pipe[0]);
//         exit();
//     } else {
//         //parent: check if other input value divides the first prime
//         while (read(input_port, &other_value, sizeof(int)) > 0) {
//             if (other_value % first_value != 0) {
//                 write(new_pipe[1], &other_value, sizeof(int));
//             }
//         }
//         wait();
//         exit();
//     }


// }


int main(int argc, char *argv[]) {
    int fd[2];
    int new_pipe[2];

    int *read_pipe;
    int *write_pipe;

    int first_received;
    int other_received;
    int result = pipe(fd);
    if (result == -1) {
        printf("create pipe error!\n");
        return -1;
    }
    
    int i;
    if (fork() > 0) {

        close(fd[0]);
        for (i = 2; i <= 35; i++) {
            result = write(fd[1], &i, sizeof(int));
        }
        close(fd[1]);
        wait();
        exit();

    } else {

        read_pipe = fd;
        write_pipe = new_pipe;

        while(1) {
            result = pipe(write_pipe);
            if (result == -1) {
                printf("create pipe error!\n");
                return -1;
            }
            close(read_pipe[1]);

            if (read(read_pipe[0], &first_received, sizeof(int))) {
                printf("prime %d\n", first_received);
            } else {
               exit();
            }

            if (fork() > 0) {
                close(write_pipe[0]);
                while(read(read_pipe[0], &other_received, sizeof(int))) {
                    if (other_received % first_received) {
                        write(write_pipe[1], &other_received, sizeof(int));
                    }
                }
                close(read_pipe[0]);
                close(write_pipe[1]);
                wait();
                exit();
            } else {
                close(read_pipe[0]);
                int *temp = read_pipe;
                read_pipe = write_pipe;
                write_pipe = temp;

            }
        }
    }
    
    return 0;
}

