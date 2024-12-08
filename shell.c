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
        char* cmd[256];
        char line[256];
        syspath();
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("EOF\n");
            exit(0); // should be zero so no error is printed
        };
        parse_semicolon(line, cmd);
        for (int i = 0; cmd[i] != NULL; i++) {
            if (strchr(cmd[i], '|') != NULL) {
                run_pipe(cmd[i]);
            } 
            // check if redirect 
            else if (strchr(cmd[i], '>') != NULL || strchr(cmd[i], '<') != NULL) {
                char* args[256];
                parse_args(cmd[i], args);
                for (int j = 0; args[j] != NULL; j++) {
                    // find array index of the redirect 
                    if (strcmp(args[j], ">") == 0 || strcmp(args[j], "<") == 0) {
                        redirect(args, j);
                    }
                }
            }

            else {
                char* args[256];
                parse_args(cmd[i], args);
                if (strcmp(args[0], "cd") == 0) {
                    run_cd(args);
                } else if (strcmp(args[0], "exit") == 0) {
                  exit(0);
                } else {
                    run_cmd(args);
                }
            }
        }

    }
}
