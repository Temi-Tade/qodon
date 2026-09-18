#ifndef SHELL_H
#define SHELL_H

#include <signal.h>
#include "qodon.h"

void run_shell_cmd(char *cmds[], char template[]);
void parse_shell_cmd(char cmd[], char template[]);
void get_shell_input(char template[]);
void launch_shell(char template[]);

#endif