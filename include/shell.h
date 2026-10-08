#ifndef SHELL_H
#define SHELL_H

#include "parser.h"

/**
 * Milestone 4: Executes an external command using fork(), execvp(), and waitpid().
 * Parent creates child process, child runs execvp, parent waits for child.
 * Returns process exit code.
 */
int execute_external_command(Command *cmd);

#endif /* SHELL_H */
