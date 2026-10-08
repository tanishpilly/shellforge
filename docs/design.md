# ShellForge — Design Document (Milestones 1–5)

## Overview

**ShellForge** is a simple Bash-like Unix shell implemented in C99 for the Open Source Software Project (OSSP) course. The current scope covers Milestones 1 through 5, focusing on basic REPL mechanics, tokenization, process execution, and parent process directory navigation.

---

## Architecture Diagram

```
+---------------------------------------------------------------------------------+
|                                    REPL Loop                                    |
|                                     (main.c)                                    |
+----------------------------------------+----------------------------------------+
                                         |
                                         v
+---------------------------------------------------------------------------------+
|                               Command Tokenizer                                 |
|                                   (parser.c)                                    |
|   - Tokenizes input using strtok_r                                              |
|   - Fills Command structure (args array ending with NULL)                       |
+----------------------------------------+----------------------------------------+
                                         |
                                         v
+----------------------------------------+----------------------------------------+
|                                Command Dispatcher                               |
|                                     (main.c)                                    |
+----------------------------------------+----------------------------------------+
                                         |
                    +--------------------+--------------------+
                    |                                         |
                    v                                         v
+---------------------------------------+ +---------------------------------------+
|            Built-in Commands          | |           External Commands           |
|              (builtins.c)             | |               (shell.c)               |
|  - cd: Navigation via chdir()         | |  - Creates child via fork()          |
|  - pwd: Working directory via getcwd()| |  - Replaces text segment via execvp()|
|  - exit: Shell exit handling          | |  - Parent waits via waitpid()         |
+---------------------------------------+ +---------------------------------------+
```

---

## Core Components (Milestones 1–5)

### 1. REPL Loop (`src/main.c`)
- Displays `shellforge$ ` prompt when running in an interactive terminal (`isatty(STDIN_FILENO)`).
- Reads dynamic line input using `getline()`.
- Handles `Ctrl+D` (EOF) and empty lines gracefully without crashing.

### 2. Tokenizer & Parser (`include/parser.h`, `src/parser.c`)
- Uses `strtok_r()` to split input into space/tab-separated tokens.
- Populates `Command` structure containing `args[64]` array and token count `count`.
- Ensures `args` array is `NULL`-terminated for execution.

### 3. Process Execution (`include/shell.h`, `src/shell.c`)
- Executes external Linux binaries (`ls`, `echo`, `whoami`, `date`, etc.).
- `fork()` spawns child process.
- Child invokes `execvp(cmd.args[0], cmd.args)`.
- Parent waits for child completion via `waitpid()`.
- Catches execution errors (e.g. `command not found`) without crashing the shell.

### 4. Built-in Navigation (`include/builtins.h`, `src/builtins.c`)
- `cd [dir]`: Changes working directory of the parent shell process via `chdir()`.
- `pwd`: Displays current working directory via `getcwd()`.
- `exit`: Terminates the shell REPL loop cleanly.
