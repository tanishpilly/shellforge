# ShellForge — A Bash-like Shell Written in C

[![Language](https://img.shields.io/badge/Language-C99-blue.svg)](https://en.wikipedia.org/wiki/C99)
[![Standard](https://img.shields.io/badge/POSIX-2008-green.svg)](https://pubs.opengroup.org/onlinepubs/9699919799/)

**ShellForge** is a simple Bash-like Unix shell written in C99 for the Open Source Software Project (OSSP) college course. This repository contains the complete project implementation through **Milestone 5**.

---

## 1. Project Overview

ShellForge provides an interactive Read-Eval-Print Loop (REPL) prompt (`shellforge$ `) that reads user command inputs, tokenizes arguments, executes built-in navigation commands, and spawns child processes for external Linux binaries.

---

## 2. Objectives

- Understand Unix process creation using `fork()`.
- Program process execution with `execvp()`.
- Synchronize process completion with `waitpid()`.
- Implement parent process directory navigation using `chdir()`.
- Write structured, modular C code using POSIX system calls.

---

## 3. Technologies Used

- **Language**: C (C99 / POSIX standard)
- **Compiler**: GCC
- **Build System**: GNU Make
- **Environment**: Linux / WSL Ubuntu

---

## 4. Milestone 1 — Initial ShellForge Framework

- REPL loop displaying `shellforge$ ` prompt.
- Dynamic line input reading via `getline()`.
- Handling `Ctrl+D` (EOF) and empty line inputs.
- Built-in `exit` command.
- GNU Makefile with `make`, `make clean`, `make debug`, and `make test` targets.

---

## 5. Milestone 2 — Tokenizer

- Simple whitespace-based tokenization using `strtok_r()`.
- Splitting user command string into discrete arguments (`args[0] = "ls"`, `args[1] = "-l"`).
- `NULL`-terminating the argument array for `execvp()` compatibility.

---

## 6. Milestone 3 — Command Structure / Organizer

- Organized structure representation:
  ```c
  typedef struct {
      char *args[64];
      int count;
  } Command;
  ```
- `parse_command()` function to parse input and fill `Command` structure.
- Safe dynamic memory management and memory freeing routines (`free_command()`).

---

## 7. Milestone 4 — Process Execution

- Process lifecycle implementation:
  - `fork()` spawns child process.
  - `execvp()` executes target binary in child process.
  - `waitpid()` waits for child completion in parent process.
- Error handling for invalid commands (`command not found`) without crashing the shell.

---

## 8. Milestone 5 — Directory Navigation (`cd`)

- Built-in `cd` command executed in parent shell process:
  - `cd` or `cd ~` changes to user `$HOME` directory.
  - `cd <folder>` changes to target directory via `chdir()`.
  - Displays appropriate error message via `perror()` if directory does not exist.
- Built-in `pwd` command displaying current directory via `getcwd()`.

---

## 9. Project Structure

```text
shellforge/
├── src/
│   ├── main.c        # REPL loop entry point
│   ├── shell.c       # Process execution (fork / execvp / waitpid)
│   ├── parser.c      # Tokenizer and Command parser
│   └── builtins.c    # Built-in commands (cd, pwd, exit)
├── include/
│   ├── shell.h
│   ├── parser.h
│   └── builtins.h
├── tests/
│   └── test_shell.sh # Automated integration test suite
├── docs/
│   └── design.md     # Architecture design document
├── Makefile          # GNU Makefile build system
├── README.md         # Project documentation
└── .gitignore
```

---

## 10. Compilation

Compile ShellForge using `make`:

```bash
make
```

To recompile with debug symbols:

```bash
make debug
```

To clean object files and binaries:

```bash
make clean
```

---

## 11. Running the Shell

Start ShellForge interactively:

```bash
./shellforge
```

Interactive prompt:

```text
shellforge$ 
```

---

## 12. Supported Commands

- `exit` — Exits the shell cleanly.
- `cd [dir]` — Changes current working directory (parent process built-in).
- `pwd` — Prints current working directory.
- `ls` / `ls -l` / `ls -a` — Lists directory contents.
- `echo [args]` — Prints text.
- `whoami` — Displays current logged-in user.
- `date` — Displays current system date and time.
- Any standard system binary available in system `$PATH`.

---

## 13. Testing

Run the automated test suite:

```bash
make test
```

Sample test output:

```text
=== Running Integration Tests ===
bash tests/test_shell.sh
=== ShellForge Integration Test Suite (Milestones 1-5) ===
[1/5] Testing basic command execution...
[2/5] Testing invalid command error handling...
[3/5] Testing built-in navigation (cd & pwd)...
[4/5] Testing system commands (whoami & date)...
[5/5] Testing empty line and exit...
=== ALL MILESTONE 1-5 TESTS PASSED CLEANLY ===
```

---

## 14. Known Limitations

- ShellForge scope is currently limited to Milestones 1–5 as required for this submission.
- Advanced features like pipelines (`|`), file redirections (`<`, `>`), background execution (`&`), and signal handling are not included in this submission milestone.

---

## Author

Developed by **Tanish Pilly**
GitHub Repository: [https://github.com/tanishpilly/shellforge](https://github.com/tanishpilly/shellforge)
