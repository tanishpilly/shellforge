#define _POSIX_C_SOURCE 200809L
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int execute_external_command(Command *cmd) {
    if (!cmd || cmd->count == 0 || !cmd->args[0]) {
        return 0;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("shellforge: fork");
        return 1;
    }

    if (pid == 0) {
        /* Child process executes external command */
        execvp(cmd->args[0], cmd->args);
        
        /* If execvp returns, an error occurred */
        if (errno == ENOENT) {
            fprintf(stderr, "shellforge: %s: command not found\n", cmd->args[0]);
        } else {
            perror(cmd->args[0]);
        }
        exit(127);
    }

    /* Parent process waits for child process to finish */
    int status;
    if (waitpid(pid, &status, 0) < 0) {
        perror("shellforge: waitpid");
        return 1;
    }

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }

    return 0;
}
