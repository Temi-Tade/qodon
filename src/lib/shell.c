#include "shell.h"
#include "qodon.h"

void run_shell_cmd(char *cmds[], char template[]) {
    if (strcmp(cmds[0], "exit") == 0) {
        printf("Exiting qodon shell...");
        raise(SIGINT);
    } else if (strcmp(cmds[0], "len") == 0) {
        get_base_length(template);
    } else if (strcmp(cmds[0], "rev") == 0) {
        reverse(template);
    } else if (strcmp(cmds[0], "cmp") == 0) {
        handle_complement(template, 0, 0);
    } else if (strcmp(cmds[0], "tr") == 0) {
        handle_complement(template,1 , 0);
    } else if (strcmp(cmds[0], "rt") == 0) {
        handle_complement(template, 0, 1);
    } else if (strcmp(cmds[0], "gc") == 0) {
        printf("%.2f%%\n", get_gc_content(template));
    } else {
        fprintf(stderr, "'%s': Invalid shell command\n", cmds[0]);
    }
}

void parse_shell_cmd(char cmd[], char template[]) {
    char *subcommands[MAX_SHELL_ARGS];
    int count = 0;
    
    char *token = strtok(cmd, " ");

    while (token != NULL && count < MAX_SHELL_ARGS) {
        subcommands[count] = token;
        count++;
        token = strtok(NULL, " ");
    }

    run_shell_cmd(subcommands, template);
}

void get_shell_input(char template[]) { 
    // get shell subcommands
    char command[MAX_CMD_LENGTH];

    printf("qdn> ");
    if (fgets(command, MAX_CMD_LENGTH, stdin) != NULL) {
        if (strcmp(command, "\n") == 0 || strcmp(command, " ") == 0) {
            fprintf(stderr, "'%s': Invalid shell command\n", command);
            get_shell_input(template);
            return;
        }
        
        command[strcspn(command, "\n")] = '\0';
        parse_shell_cmd(command, template);
    } else {
        fprintf(stderr, "Command error");
    }

    get_shell_input(template);
}

void launch_shell(char template[]) {
    size_t length = strlen(template);

    printf("Entering qodon shell...\n");
    printf("Template sequence: %s \nLength: %ldbps \nGC content: %.2f%%\n", template, length, get_gc_content(template));

    get_shell_input(template);
}