# Pipex

Recreates the Unix pipeline flow for two commands in C, including redirection, process control, and command execution.

## Overview

Pipex was built as part of the 42 curriculum to deepen low-level understanding of how shells execute piped commands. The project reproduces the behavior of:

```bash
< infile cmd1 | cmd2 > outfile
```

It focuses on reliable process orchestration, file descriptor management, and clear failure handling under real command-line edge cases.

## Demo / Screenshots

Add your visual assets here:

- CLI demo GIF placeholder: ![Pipex demo GIF](docs/demo.gif)
- Terminal run screenshot placeholder: ![Pipex terminal screenshot](docs/screenshot-terminal.png)
- Validation tests screenshot placeholder: ![Pipex tests screenshot](docs/screenshot-tests.png)

## Tech Stack

- Language: C
- Build system: Make
- Library: custom Libft
- Platform: Unix/Linux
- Core system calls: fork, execve, pipe, dup2, waitpid, open, access
- Compiler flags: -Wall -Wextra -Werror

## Architecture / Implementation

The codebase is intentionally modular and split by responsibility:

- main.c
Initializes state, validates input, runs the execution path, and handles cleanup.
- parse.c
Parses command arguments, extracts PATH entries, and resolves executable paths.
- exec.c
Handles file checks, process creation, piping, redirection, and exit status propagation.
- error_and_exit.c
Centralizes user-facing errors and failure exits.

Key implementation decisions:

- Uses a dedicated state struct to keep command paths, arguments, and runtime data together.
- Returns the last command exit status to align with shell behavior.
- Handles invalid input or missing first command by redirecting stdin from /dev/null so the second command can still execute when applicable.

## Features

- Reproduces two-command pipeline behavior in C
- Supports file redirection for input and output
- Resolves commands through PATH and absolute paths
- Handles command-not-found and file permission errors
- Preserves deterministic cleanup for memory and file descriptors
- Returns exit codes consistent with expected shell behavior

## Getting Started

1. Clone the repository.
2. Move into the project directory.
3. Build the executable.
4. Run Pipex with input file, two commands, and output file.

```bash
git clone https://github.com/chilituna/pipex.git
cd pipex/pipex
make
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

## Project Structure

```text
.
├── README.md
└── pipex/
	├── Makefile
	├── includes/
	│   └── pipex.h
	├── src/
	│   ├── main.c
	│   ├── parse.c
	│   ├── exec.c
	│   └── error_and_exit.c
	├── Libft/
	│   └── ...
	└── pipex_tests/
		└── ...
```

## Future Improvements

- Add support for quoted arguments and more advanced shell parsing
- Extend to multi-command pipelines (bonus-style behavior)
- Improve automated test coverage and add CI checks
- Add benchmark scripts for process and I/O scenarios

## What I Learned

- How Unix pipelines work internally through process and descriptor control
- How to combine fork, execve, pipe, and dup2 safely
- How to design predictable error flows and cleanup in C
- How to structure a systems project in small, maintainable modules

## Licence

This project is licensed under the MIT License. See the LICENSE file for details.

