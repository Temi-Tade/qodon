#ifndef QODON_H
#define QODON_H

#include <stdio.h>
#include <string.h>

#define MAX_SHELL_ARGS 3
#define MAX_CMD_LENGTH 10

int validate(char template[], int is_transcribing, int is_rt);
void get_complementary_sequence(char template[], char complement[], int is_transcribing, int is_rt);
void handle_complement(char input[], int is_transcribing, int is_rt);
void get_base_length(char template[]);
void transcribe(char template[]);
void reverse(char forward[]);
float get_gc_content(char sequence[]);

#endif