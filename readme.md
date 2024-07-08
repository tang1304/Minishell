# Minishell
This project is about recreating a minimalist version of a shell. Shells are command line interfaces (CLI), that were first used when computers didn't have graphical user interfaces (GUI), to interact with operating systems.

## Mandatory part:

### Authorized functions:
	readline, rl_clear_history, rl_on_new_line,
	rl_replace_line, rl_redisplay, add_history,
	printf, malloc, free, write, access, open, read,
	close, fork, wait, waitpid, wait3, wait4, signal,
	sigaction, sigemptyset, sigaddset, kill, exit,
	getcwd, chdir, stat, lstat, fstat, unlink, execve,
	dup, dup2, pipe, opendir, readdir, closedir,
	strerror, perror, isatty, ttyname, ttyslot, ioctl,
	getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
	tgetnum, tgetstr, tgoto, tputs


### Objectives:

The shell should:

  - Display a prompt when waiting for a new command.

  - Have a working history.

  - Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path).

  - Avoid using more than one global variable to indicate a received signal. Consider
the implications: this approach ensures that your signal handler will not access your
main data structures.

  - Not interpret unclosed quotes or special characters which are not required by the
subject such as `\` (backslash) or `;` (semicolon).

  - Handle `’` (single quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence.

  - Handle `"` (double quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence except for `$` (dollar sign).

  - Implement redirections:
	- `<` should redirect input.
	- `>` should redirect output.
	- `<<` should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
	- `>>` should redirect output in append mode.

  - Implement pipes `|`. The output of each command in the pipeline is
connected to the input of the next command via a pipe.

  - Handle environment variables (`$` followed by a sequence of characters) which
should expand to their values.

  - Handle `$?` which should expand to the exit status of the most recently executed
foreground pipeline.

  - Handle `ctrl-C`, `ctrl-D` and `ctrl-\` which should behave like in bash.

  - In interactive mode:
	- `ctrl-C` displays a new prompt on a new line.
	- `ctrl-D` exits the shell.
	- `ctrl-\` does nothing.

  - Your shell must implement the following builtins:
	- echo with option -n
	- cd with only a relative or absolute path
	- pwd with no options
	- export with no options
	- unset with no options
	- env with no options or arguments
	- exit with no options

## Bonus part:

The program has to implement:

  - `&&` and `||` with parenthesis for priorities.

  - Wildcard `*` should work for the current working directory.

## Usage:

Run "make" to compile the project, then "./minishell" to execute it.

To ignore leaks due to 'readline' function:
```
valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full --track-fds=yes --show-leak-kinds=all --track-origins=yes --verbose --show-mismatched-frees=yes --read-var-info=yes
```
