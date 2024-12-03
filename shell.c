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

int main() {
    while (1) {
        char** cmd_list[256];
        char* cmd[256];
        char line[256];
        printf("Enter Command : \n");
        fgets(line, sizeof(line), stdin);
        parse_semicolon(line, cmd);
        for (int i = 0; cmd[i] != NULL; i++) {
            char* args[25];
            parse_args(cmd[i], args);
            // fork and execvp each command 
            execvp(args[0], args);            
        }
        // if (strchr(';', cmd) == NULL) {
        //     parse_args(line, cmd);
        // } else {
        //     parse_semicolon(line, cmd_list);
        // }
        //printf("%s", cmd);
        //execvp(cmd[0], cmd);
    }
}
