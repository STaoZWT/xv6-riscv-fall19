#include "kernel/types.h"
#include "user/user.h"
/*
    Edited by Wentao Zhang 
    2020/10/21
*/
int main(int argc, char *argv[]) {
    int i;

    if (argc != 2) {
        printf("please input correct arguments\n");
        exit();
    }

    i = atoi(argv[1]);
    sleep(i);
    exit();
}
