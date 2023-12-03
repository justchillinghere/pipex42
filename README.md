# Pipex 42

## Description

This program takes the infile, outfile to redirect the STDIN (<), STDOUT (>) and 2 commands to pipe. To execute the mandatory program, type the command listed below:

```bash
./pipex file1 cmd1 cmd2 file2
```

The arguments will be processed as same as `< file1 cmd1 | cmd2 > file2 ` on the shell.

## Mandatory part

It must take 4 arguments:
• file1 and file2 are file names.
• cmd1 and cmd2 are shell commands with their parameters.

## Allowed external functions

Std: open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid

Libft: allowed

## Examples of work

```bash
./pipex infile "ls -l" "wc -l" outfile # is the same as
< infile ls -l | wc -l >
```

```bash
./pipex infile "grep a1" "wc -w" outfile # is the same as
< infile grep a1 | wc -w >
```
