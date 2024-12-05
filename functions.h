#ifndef functions_h
#define functions_h
void parse_args( char * line, char ** arg_ary );
void parse_semicolon(char* line, char ** list);
void parse_pipe(char* line, char ** list);
void error();
void syspath();
void run_cmd(char **args);
void run_cd(char ** args);
void run_pipe(char * line);
#endif
