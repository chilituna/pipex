# Pipex

`pipex` is a production-style CLI project in C that reproduces Unix pipe behavior between two commands.

It was built as part of the 42 curriculum and scored `100/100`.

## Project Highlights

- **Scope**: Reproduces shell-equivalent command chaining for two commands
- **Core competencies**: Process control, I/O redirection, error handling, modular C design
- **Engineering focus**: Reliability under edge cases, predictable exit codes, memory and FD safety
- **Result**: 42 project graded `100/100`

It implements the behavior of:

```bash
< infile cmd1 | cmd2 > outfile
```

while handling process creation, file descriptor redirection, command resolution through `PATH`, and exit status propagation.

## Tech Stack

- **Language**: C
- **Environment**: Unix/Linux
- **System calls**: `fork`, `execve`, `pipe`, `dup2`, `waitpid`, `open`, `access`
- **Build**: Makefile (`-Wall -Wextra -Werror`)

## Why This Project Matters

This project demonstrates core software engineering skills that are relevant beyond systems programming:

- Translating requirements into a reliable CLI product with clear behavior
- Designing a modular codebase (`parse`, `exec`, `error`, `main`) with single-purpose files
- Building robust error handling and predictable exit codes
- Writing defensive file and input handling for edge cases
- Managing resources carefully (memory, file descriptors, child processes)

## Build

From the repository root:

```bash
cd pipex
make
```

Compiler flags: `-Wall -Wextra -Werror`.

## Usage

```bash
./pipex <infile> "<cmd1>" "<cmd2>" <outfile>
```

Example:

```bash
./pipex pipex_tests/test_in "grep hello" "wc -l" pipex_tests/test_out
```

Equivalent shell command:

```bash
< pipex_tests/test_in grep hello | wc -l > pipex_tests/test_out
```

## Behavior and Edge Cases

- Resolves command paths from `PATH` (and accepts absolute command paths).
- Returns the exit status of the last executed command.
- Handles missing/unreadable input files.
- Handles non-writable output files.
- Prints `command not found` style errors when commands cannot be resolved.
- Falls back to `/dev/null` input when the first command or input file is invalid, so the second command can still run.

## Project Structure

```text
pipex/
	includes/      # headers
	src/           # core implementation (parse, exec, errors, main)
	Libft/         # custom C standard library utilities
	pipex_tests/   # local test files
	Makefile
```

## Implementation Notes

- `src/parse.c`: parses arguments, resolves executable paths
- `src/exec.c`: sets up redirections, pipe flow, and child execution
- `src/error_and_exit.c`: centralized error output and exit behavior
- `src/main.c`: lifecycle orchestration and cleanup

## Quality Signals

- Strict compiler warnings enabled (`-Wall -Wextra -Werror`)
- Clear separation of responsibilities across source files
- Explicit cleanup paths for allocated memory and runtime resources
- Local test assets included in `pipex/pipex_tests/`

## What I Learned

- How Unix pipelines work internally through file descriptors
- How to structure multi-process execution safely
- How to design deterministic behavior around failures and invalid inputs
- How to keep C code maintainable with explicit ownership and cleanup rules

## References

- **A comprehensive Pipex guide**: https://reactive.so/post/42-a-comprehensive-guide-to-pipex  
	Used as a high-level roadmap to validate project expectations, required behaviors, and common implementation pitfalls.
- **Code Vault C systems playlist (fork/pipe/dup2/exec focus)**: https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FmErobw8YyTwXDUE5nPH5lH  
	Used to strengthen understanding of process control and file descriptor redirection before implementing the execution flow.

