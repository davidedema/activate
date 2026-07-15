# Activate

A lightweight C command-line tool to discover and activate Python virtual environments.

`activate` scans a directory tree, identifies possible Python environments, and helps the user activate the selected environment from the current shell.

## Features

- Recursively scans directories looking for Python virtual environments
- Detects environments using a simple heuristic:
  - presence of a `bin/` directory
  - presence of `bin/activate`
  - presence of a Python executable
- Supports multiple environments in the same project tree
- Automatically activates a single detected environment
- Interactive selection when multiple environments are found
- Lightweight C implementation with no external dependencies

## Important info

- Current version supprorts only linux/MacOS
- The project is currently under development so bugs are expected 

# Project structure

```
activate
├── include
│   ├── activate.h
│   ├── dir_list.h
│   ├── io.h
│   └── scan.h
│
├── src
│   ├── main.c
│   ├── activate.c
│   ├── dir_list.c
│   ├── scan.c
│   └── io.c
│
├── scripts
│   └── activate
│
├── Makefile
└── README.md
```


# Building

Requirements:

* GCC or another C compiler
* POSIX-compatible system

Build:

```bash
make
```

The generated binary is:

```text
activate-cli
```


# Installation

Install for the current user:

```bash
make install PREFIX=$HOME/.local
```

This installs:

```
~/.local/bin/activate-cli
~/.local/bin/activate
```

Make sure `~/.local/bin` is in your `PATH`:

```bash
export PATH="$HOME/.local/bin:$PATH"
```

Add this 3 lines in the `~/.bashrc` and you are ready to go

```bash
activate() {
    source "$HOME/.local/bin/activate" "$@"
}
```

# Usage

## Scan current directory

```bash
activate
```

The current directory is used as the search root.


## Scan a specific directory

```bash
activate /path/to/project
```

Example:

```
project/
├── env/
│   └── bin/
│       ├── activate
│       └── python
│
└── experiments/
    └── .venv/
        └── bin/
            ├── activate
            └── python
```

The tool detects both environments.



## Multiple environments

When multiple environments are found:

```
Multiple environments found:

1) /home/user/project/env/bin/activate
2) /home/user/project/experiments/.venv/bin/activate

Select environment:
```

The selected environment is sourced into the current shell.



# Environment detection

Currently an environment is considered valid if:

```
environment/
└── bin/
    ├── activate
    └── python
```



# Future improvements

* Better error handling
* Cache discovered environments
* Environment names instead of full paths
* Shell completion
* Support for zsh/fish
* Package distribution