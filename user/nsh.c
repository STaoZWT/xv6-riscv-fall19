#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

/**
 * Edited by Wentao Zhang
 * 2020/11/10
 */

char args[100][100];

void parsecmd(int *argc, char *argv[], char *cmd) {
  for (int i = 0; i < 100; i++) {
    argv[i] = &args[i][0];
  }
  int i = 0, j = 0;
  //while (cmd[j] != '\n' && cmd[j] != '\0') {
  for (i = 0, j = 0; cmd[j] != '\n' && cmd[j] != '\0'; j++) {
    while (
      cmd[j] == ' ' || 
      cmd[j] == '\t' || cmd[j] == '\n' || cmd[j] == '\r' || cmd[j] == '\f') {
        j++;
    }
    argv[i] = cmd + j;
    i++;
    while (
      cmd[j] != ' ' && 
      cmd[j] != '\t' && cmd[j] != '\n' && cmd[j] != '\r' && cmd[j] != '\f') {
        j++;
    }
    cmd[j] = '\0';
    //j++;
  }
  argv[i] = 0;
  *argc = i;
}
  


int getcmd(char *buf, int nbuf) {
  fprintf(2, "@ ");
  memset(buf, 0, nbuf);
  gets(buf, nbuf);
  if (buf[0] == 0) //EOF
    return -1;
  return 0;
}

void runpipe(int argc, char *argv[]);

void runcmd(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "|")) {
      runpipe(argc, argv);
    }
  }
  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], ">")) {
      close(1);
      open(argv[i+1], O_CREATE|O_WRONLY);
      argv[i] = 0;
    }

    if (!strcmp(argv[i], "<")) {
      close(0);
      open(argv[i+1], O_RDONLY);
      argv[i] = 0;
    }
    
  }
  exec(argv[0], argv);
}

void runpipe(int argc, char *argv[]) {
  int fd[2];
  int i = 0;

  while (1) {
    if (!strcmp(argv[i], "|")) {
      argv[i] = 0;
      break;
    } else if (i == argc) {
      break;
    }
    i++;
  }

  pipe(fd);
  if (fork() == 0) {
    //child
    close(1);
    dup(fd[1]);
    close(fd[1]);
    close(fd[0]);
    runcmd(i, argv);
  } else {
    //parent
    close(0);
    dup(fd[0]);
    close(fd[0]);
    close(fd[1]);
    runcmd(argc-i-1, argv+i+1);
  }

}

int main(int argc, char *argv[]) {
  static char buf[100];

  while(getcmd(buf, sizeof(buf)) >= 0) {

    if (fork() == 0) {
      //child
      char *argv[100];
      int argc = -1;
      parsecmd(&argc, argv, buf);
      runcmd(argc, argv);
    } 
    wait(0);

  }

  exit(0);
}


