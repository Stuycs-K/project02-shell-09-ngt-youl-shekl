#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include "functions.h"


void run_cmd(char **args) {
  pid_t p = fork();
  if (p < 0) {
    perror("fork failed");
    exit(1);
  }
  else if (p == 0) {
    execvp(args[0], args);
  }
  else {
    // parent
    int status;
    pid_t childPid = wait(&status);
    if (childPid == -1) {
      perror("wait error");
      exit(1);
    }
    // printf("command done\n");
  }
}


int main() {
    while (1) {
        char* cmd[256];
        char line[256];
        printf("Enter Command :  ");
        fgets(line, sizeof(line), stdin);
        parse_semicolon(line, cmd);
        for (int i = 0; cmd[i] != NULL; i++) {
            char* args[256];
            parse_args(cmd[i], args);
            //execvp(args[0], args);
            run_cmd(args);
        }
    }
}
