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
            if (strcmp(args[0], "cd") == 0) {
                run_cd(args);
            } else {
                run_cmd(args);
            }
        }

    }
}
