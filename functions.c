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

void parse_args( char * line, char ** arg_ary ) {
  char *token;
  int index = 0;
  while (token = strsep(&line, " \n")) {
    if (token[0] != '\0') {
      arg_ary[index] = token;
      index++;
    }
  }
  arg_ary[index] = NULL;
}

void parse_semicolon(char* line, char ** list) {
  int list_index = 0;
  char* cmd_token;
  while (cmd_token = strsep(&line, ";\n")) {
    if (cmd_token[0] != '\0') {
      list[list_index] = cmd_token;
      list_index++;
    }
  }
  list[list_index] = NULL;
}

void syspath() {
  char * cwd;
  char buff[PATH_MAX];
  cwd = getcwd(buff, PATH_MAX);
  printf("%s$ ", cwd);
  fflush(stdout);
}

void pathch() {

}

void error() {
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

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
    int status;
    pid_t childPid = wait(&status);
    if (childPid == -1) {
      perror("wait error");
      exit(1);
    }
  }
}

void run_cd(char ** args) {
    char curr_dir[256];
    if (getcwd(curr_dir, sizeof(curr_dir)) == NULL) {
        perror("curr getcwd() error\n");
    }
    printf("curr dir : %s\n", curr_dir);
    printf("change dir : %s\n", args[1]);
    if (chdir(args[1]) != 0) {
        perror("chdir() failed\n");
    }
    char new_dir[256];
    if (getcwd(new_dir, sizeof(new_dir)) == NULL) {
        perror("new getcwd() error\n");
    }
    printf("new dir : %s\n", new_dir);
}
