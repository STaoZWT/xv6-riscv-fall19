#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {

    char read_buf[512];
    char *exec_args[MAXARG];
    char input_args[MAXARG][MAXARG];
    int read_length;

    for (int i = 0; i < MAXARG; i++) {
        exec_args[i] = input_args[i];
    }

    for (int i = 1; i < argc; i++) {
        strcpy(input_args[i-1], argv[i]);
    }

    while ((read_length = read(0, read_buf, sizeof(read_buf))) > 0) {
        int pos = argc - 1;
        char *c = input_args[pos];
        for (int i = 0; i < read_length; i++) {
            switch(read_buf[i]) {
                case '\n':
                    *c = '\0';
                    exec_args[pos] = input_args[pos];
                    pos++;
                    exec_args[pos] = 0;
                    pos = argc - 1;
                    if (fork() == 0) {
                        exec(exec_args[0], exec_args);
                    } else {
                        wait();
                    }
                    c = input_args[pos];
                    break;
                case ' ':
                    *c = '\0';
                    exec_args[pos] = input_args[pos];
                    pos++;
                    c = input_args[pos];
                    break;
                default:
                    *c = read_buf[i];
                    c++;
            }
        }
    }

    return 0;
}