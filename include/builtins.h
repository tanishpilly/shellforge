#ifndef BUILTINS_H
#define BUILTINS_H

#include "parser.h"

/**
 * Checks if a command is a shell built-in command (cd, pwd, exit).
 * Returns 1 if built-in, 0 otherwise.
 */
int is_builtin(const char *cmd_name);

/**
 * Executes a built-in command in the parent shell process.
 * Handles directory navigation (cd), printing working directory (pwd), and exit.
 * Returns 0 on success, non-zero on error. Sets should_exit flag if exit is requested.
 */
int execute_builtin(Command *cmd, int *should_exit);

#endif /* BUILTINS_H */
