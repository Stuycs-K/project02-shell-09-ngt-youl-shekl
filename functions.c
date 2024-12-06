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

void parse_args(char *line, char **arg_ary)
{
  char *token;
  int index = 0;
  while (token = strsep(&line, " \n"))
  {
    if (token[0] != '\0')
    {
      arg_ary[index] = token;
      index++;
    }
  }
  arg_ary[index] = NULL;
}

void parse_semicolon(char *line, char **list)
{
  int list_index = 0;
  char *cmd_token;
  while (cmd_token = strsep(&line, ";\n"))
  {
    if (cmd_token[0] != '\0')
    {
      list[list_index] = cmd_token;
      list_index++;
    }
  }
  list[list_index] = NULL;
}

void parse_pipe(char *line, char **list)
{
  int list_index = 0;
  char *cmd_token;
  while (cmd_token = strsep(&line, "|\n"))
  {
    if (cmd_token[0] != '\0')
    {
      list[list_index] = cmd_token;
      list_index++;
    }
  }
  list[list_index] = NULL;
}

void syspath()
{
  char *home = getenv("HOME");
  size_t homelen = strlen(home);
  char *cwd;
  char buff[PATH_MAX];
  cwd = getcwd(buff, PATH_MAX);
  size_t cwdlen = strlen(cwd);
  if (strncmp(home, cwd, homelen) == 0)
  {
    cwd += homelen;
    char newcwd[PATH_MAX];
    sprintf(newcwd, "~%s", cwd);
    printf("%s$ ", newcwd);
    fflush(stdout);
  }
  else
  {
    printf("%s$ ", cwd);
    fflush(stdout);
  }
}

void error()
{
  printf("errno %d\n", errno);
  printf("%s\n", strerror(errno));
  exit(1);
}

void run_cmd(char **args)
{
  pid_t p = fork();
  if (p < 0)
  {
    perror("fork failed");
    exit(1);
  }
  else if (p == 0)
  {
    execvp(args[0], args);
  }
  else
  {
    int status;
    pid_t childPid = wait(&status);
    if (childPid == -1)
    {
      perror("wait error");
      exit(1);
    }
  }
}

void run_cd(char **args)
{
  char curr_dir[256];
  if (getcwd(curr_dir, sizeof(curr_dir)) == NULL)
  {
    perror("curr getcwd() error\n");
  }
  if (args[1] == NULL)
  {
    printf("typing just 'cd' not supported in this version\n");
  }
  else
  {
    if (chdir(args[1]) != 0)
    {
      perror("chdir() failed\n");
    }
  }
  char new_dir[256];
  if (getcwd(new_dir, sizeof(new_dir)) == NULL)
  {
    perror("new getcwd() error\n");
  }
}

void redirect(char **args, int index)
{
  // redirect stdout
  if (strcmp(args[index], ">") == 0)
  {
    int fd1 = open(args[index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd1 == -1)
    {
      perror("file open error");
      exit(1);
    }
    int backup_stdout = dup(STDOUT_FILENO);
    dup2(fd1, STDOUT_FILENO);
    args[index] = NULL;
    run_cmd(args);
    // char cmd[256];
    // int cmd_index = 0;
    // for (int i = 0; i < index; i++) {
    //   for (int j = 0; j < strlen(args[i]); j++) {
    //     cmd[cmd_index] = args[i][j];
    //     cmd_index++;
    //   }
    //   cmd[cmd_index] = ' ';
    //   cmd_index++;
    // }
    // cmd[cmd_index] = '\0';

    fflush(stdout);
    dup2(backup_stdout, STDOUT_FILENO);
  }
  // redirect stdin
  else
  {
    printf("in file: %s\n", args[index + 1]);
    printf("out file: %s\n", args[index - 1]);
  }
}

void run_pipe(char *line)
{
  // there is a space before second cmd, might be a problem
  char *cmd[10];
  parse_pipe(line, cmd);
  // for (int i = 0; cmd[i] != NULL; i++) {
  //   printf("%s\n", cmd[i]);
  // }

  FILE *first_cmd;
  char stdout_info[1024];
  first_cmd = popen(cmd[0], "r");
  if (first_cmd == NULL)
  {
    perror("first cmd popen failed");
  }

  FILE *scnd_cmd;
  scnd_cmd = popen(cmd[1], "w");
  if (scnd_cmd == NULL)
  {
    perror("second cmd popen failed");
  }

  while (fgets(stdout_info, sizeof(stdout_info), first_cmd) != NULL)
  {
    // printf("%s\n", stdout_info);
    fputs(stdout_info, scnd_cmd);
  }

  fclose(first_cmd);

  fclose(scnd_cmd);
}
