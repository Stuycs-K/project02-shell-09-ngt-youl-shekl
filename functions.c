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
  while (token = strsep(&line, " ")) {
    arg_ary[index] = token;
    index++;
  }
  arg_ary[index] = NULL;
}

void parse_semicolon(char* line, char ** list) {
  int list_index = 0;
  char* cmd_token
  while (cmd_token = strsep(&line, ";")) {
    char* cmd[256];
    parse_args(cmd_token, cmd);
    list[list_index] = cmd;
    list_index++;
  }
  list[list_index] = NULL;
}
void error() {
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}