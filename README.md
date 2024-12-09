[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Tfg6waJb)
# Systems Project2 - MyShell

## [insert creative team name here]

## Features 
- any commands from the terminal that execvp can run
- cd
- prompt is shorted to ~/ ...
- prompt is also colored blue 
- pipe
- redirect: basic redirection with just one > or < works

## Attempted  Features
- allowing cd command to work with just 'cd ~' or 'cd' to go to home path

## Bugs
- pressing Ctrl-D or typing exit should end the program but sometimes it doesn't work ... no idea why, but it seems to be fine most of the time?

## Function Headers
- void parse_args( char * line, char ** arg_ary );
- void parse_semicolon(char* line, char ** list);
- void parse_pipe(char* line, char ** list);
- void error();
- void syspath();
- void run_cmd(char **args);
- void run_cd(char ** args);
- void redirect(char **args, int index);
- void run_pipe(char * line);