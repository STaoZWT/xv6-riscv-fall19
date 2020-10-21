#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int i;

    if (argc > 2) {
        printf("too many arguments");
        exit();
    }

    i = atoi(argv[1]);
    sleep(i);
    exit();
}
