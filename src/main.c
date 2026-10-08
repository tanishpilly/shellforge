#define _POSIX_C_SOURCE 200809L
#include "shell.h"
#include "parser.h"
#include "builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    char *line = NULL;
    size_t line_cap = 0;
    int is_interactive = isatty(STDIN_FILENO);
    int should_exit = 0;

    /* REPL loop */
    while (!should_exit) {
        if (is_interactive) {
            printf("shellforge$ ");
            fflush(stdout);
        }

        ssize_t nread = getline(&line, &line_cap, stdin);
        if (nread == -1) {
            /* EOF / Ctrl+D */
            if (is_interactive) {
                printf("\n");
            }
            break;
        }

        /* Strip trailing newline character */
        if (nread > 0 && line[nread - 1] == '\n') {
            line[nread - 1] = '\0';
        }

        /* Tokenize and parse input into Command structure */
        Command cmd;
        if (parse_command(line, &cmd) < 0) {
            /* Empty input line */
            continue;
        }

        /* Check for built-in commands (cd, pwd, exit) or execute external process */
        if (is_builtin(cmd.args[0])) {
            execute_builtin(&cmd, &should_exit);
        } else {
            execute_external_command(&cmd);
        }

        /* Free memory allocated for command arguments */
        free_command(&cmd);
    }

    if (line) {
        free(line);
    }

    return 0;
}
