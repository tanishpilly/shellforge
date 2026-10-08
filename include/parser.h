#ifndef PARSER_H
#define PARSER_H

#define MAX_ARGS 64

/**
 * Command structure to store tokenized command and arguments.
 * As taught in Milestones 2 & 3:
 * - args array contains command and arguments ending with NULL
 * - count stores total number of argument tokens
 */
typedef struct {
    char *args[MAX_ARGS];
    int count;
} Command;

/**
 * Tokenizes and parses user input string into a Command structure.
 * Returns 0 on success, or -1 if input is empty or invalid.
 */
int parse_command(char *line, Command *cmd);

/**
 * Frees memory allocated for command arguments.
 */
void free_command(Command *cmd);

#endif /* PARSER_H */
