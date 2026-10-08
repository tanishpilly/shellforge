#define _POSIX_C_SOURCE 200809L
#include "builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int is_builtin(const char *cmd_name) {
    if (!cmd_name) return 0;
    if (strcmp(cmd_name, "cd") == 0 ||
        strcmp(cmd_name, "pwd") == 0 ||
        strcmp(cmd_name, "exit") == 0) {
        return 1;
    }
    return 0;
}

int execute_builtin(Command *cmd, int *should_exit) {
    if (!cmd || cmd->count == 0) {
        return 0;
    }

    const char *name = cmd->args[0];

    /* Milestone 5: Navigation via cd (chdir in parent process) */
    if (strcmp(name, "cd") == 0) {
        const char *target = NULL;
        if (cmd->count == 1 || strcmp(cmd->args[1], "~") == 0) {
            target = getenv("HOME");
            if (!target) {
                fprintf(stderr, "shellforge: cd: HOME not set\n");
                return 1;
            }
        } else {
            target = cmd->args[1];
        }

        if (chdir(target) != 0) {
            perror("shellforge: cd");
            return 1;
        }
        return 0;
    }

    /* Built-in pwd command */
    if (strcmp(name, "pwd") == 0) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd))) {
            printf("%s\n", cwd);
            return 0;
        } else {
            perror("shellforge: pwd");
            return 1;
        }
    }

    /* Built-in exit command */
    if (strcmp(name, "exit") == 0) {
        if (should_exit) {
            *should_exit = 1;
        }
        return 0;
    }

    return 0;
}
