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
        // char** cmd_list[256];
        char* cmd[256];
        char line[256];
        syspath();
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("EOF\n");
            exit(1);
        };
        parse_semicolon(line, cmd);
        for (int i = 0; cmd[i] != NULL; i++) {
            char* args[256];
            parse_args(cmd[i], args);
            for (int j = 0; args[j] != NULL; j++) {
                // printf("'%s'\n", args[j]);
              if (strcmp(args[j], ">") == 0 || strcmp(args[j], "<") == 0) {
                redirect(args, j);
              }
            }
            if (strcmp(args[0], "cd") == 0) {
                run_cd(args);
            } else {
                run_cmd(args);
            }
        }

    }
}
