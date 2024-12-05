#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <signal.h>
#include "functions.h"
#define PATH_MAX 1024


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
    if (chdir(args[1]) != 0) {
        perror("chdir() failed\n");
    }
    char new_dir[256];
    if (getcwd(new_dir, sizeof(new_dir)) == NULL) {
        perror("new getcwd() error\n");
    }
}


void redirect(char **args, int index) {
  // redirect stdout
  if (strcmp(args[index], ">") == 0) {
    printf("in file: %s\n", args[index - 1]);
    printf("out file: %s\n", args[index + 1]);
    int fd1 = open(args[index + 1], O_WRONLY | O_CREAT);
    int FILENO = STDOUT_FILENO;
    int backup_stdout = dup(FILENO); // save stdout for later
    dup2(fd1, FILENO); //sets FILENO's entry to the file for fd1.
    // printf("TO THE FILE!!!\n");
    fflush(stdout);//not needed when a child process exits, becaue exiting a process will flush automatically.
    dup2(backup_stdout, FILENO); //sets FILENO's entry to backup_stdout, which is stdout
  }
  // redirect stdin
  else {
    printf("in file: %s\n", args[index + 1]);
    printf("out file: %s\n", args[index - 1]);
  }
  // int fd1 = open("foo.txt", O_WRONLY);
  // int FILENO = STDOUT_FILENO;
  // int backup_stdout = dup( FILENO ) // save stdout for later
  // dup2(fd1, FILENO) //sets FILENO's entry to the file for fd1.
  // printf("TO THE FILE!!!\n");
  // fflush(stdout);//not needed when a child process exits, becaue exiting a process will flush automatically.
  // dup2(backup_stdout, FILENO) //sets FILENO's entry to backup_stdout, which is stdout


}
