#ifndef functions_h
#define functions_h
void parse_args( char * line, char ** arg_ary );
void parse_semicolon(char* line, char ** list);
void error();
void run_cmd(char **args);
#endif
