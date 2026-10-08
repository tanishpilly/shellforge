#define _POSIX_C_SOURCE 200809L
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_command(char *line, Command *cmd) {
    if (!line || !cmd) {
        return -1;
    }

    cmd->count = 0;
    for (int i = 0; i < MAX_ARGS; i++) {
        cmd->args[i] = NULL;
    }

    char *saveptr = NULL;
    char *token = strtok_r(line, " \t\r\n", &saveptr);

    while (token != NULL && cmd->count < MAX_ARGS - 1) {
        cmd->args[cmd->count] = strdup(token);
        if (!cmd->args[cmd->count]) {
            break;
        }
        cmd->count++;
        token = strtok_r(NULL, " \t\r\n", &saveptr);
    }

    cmd->args[cmd->count] = NULL;
    return (cmd->count > 0) ? 0 : -1;
}

void free_command(Command *cmd) {
    if (!cmd) {
        return;
    }
    for (int i = 0; i < cmd->count; i++) {
        if (cmd->args[i]) {
            free(cmd->args[i]);
            cmd->args[i] = NULL;
        }
    }
    cmd->count = 0;
}
