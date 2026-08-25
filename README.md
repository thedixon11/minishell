*This project has been created as part of the 42 curriculum by jvasconc and ageoffro.*

# Minishell

## Description

**Minishell** is a simplified re-implementation of a Unix shell, written in C as
part of the 42 core curriculum. The goal of the project is to understand, from
the ground up, how a command-line interpreter like `bash` actually works: how
it reads and parses user input, how it manages processes, pipes, and file
descriptors, and how it exposes a small set of built-in commands.

The shell reads a line of input, parses it into commands, handles quoting,
environment variable expansion, redirections and pipes, then executes the
result — either by running a built-in directly or by forking a child process
and calling the corresponding executable found via `PATH` (or a relative /
absolute path).

Mandatory features implemented:
- An interactive prompt with a working command history.
- Execution of binaries found via `PATH`, or via a relative/absolute path.
- Single quotes (`'`) and double quotes `"` (with `$` expansion preserved in `"`).
- Redirections: `<`, `>`, `>>`, and `<<` (heredoc).
- Pipes (`|`) chaining any number of commands.
- Environment variable expansion (`$VAR`) and exit status expansion (`$?`).
- Signal handling for `Ctrl-C`, `Ctrl-D` and `Ctrl-\` matching bash's behavior
  in interactive mode.
- Built-in commands: `echo` (`-n`), `cd`, `pwd`, `export`, `unset`, `env`,
  `exit`.

This project does not implement the bonus part (logical operators `&&` / `||`
with parentheses, and wildcard expansion `*`) — only the mandatory part is
covered.

## Instructions

### Requirements

- A Unix-like environment (Linux or macOS).
- `cc` and `make`.
- The `readline` development library (e.g. `libreadline-dev` on
  Debian/Ubuntu, `readline` via Homebrew on macOS).

### Compilation

```bash
git clone <your-repo-url>
cd minishell
make
```

The `Makefile` provides the following rules:

| Rule      | Description                                      |
|-----------|---------------------------------------------------|
| `all`     | Builds the `minishell` executable (default rule). |
| `clean`   | Removes object files.                              |
| `fclean`  | Removes object files and the executable.           |
| `re`      | Equivalent to `fclean` followed by `all`.          |

If the project uses `libft`, it is compiled automatically from the `libft/`
folder via its own `Makefile` before the rest of the project is linked.

### Usage

```bash
./minishell
```

This launches the interactive prompt. From there, it behaves like a regular
shell:

```bash
minishell$ echo "Hello, world!"
Hello, world!
minishell$ ls -l | grep .c | wc -l
3
minishell$ export GREETING=hi && echo $GREETING   # (&& is bonus, not implemented)
minishell$ exit
```

Press `Ctrl-D` on an empty line, or run `exit`, to leave the shell.

## Resources

### Documentation & references

- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [GNU Readline Library documentation](https://tiswww.case.edu/php/chet/readline/rltop.html)
- `man` pages: `readline(3)`, `fork(2)`, `execve(2)`, `pipe(2)`, `dup2(2)`,
  `wait(2)`/`waitpid(2)`, `signal(2)`/`sigaction(2)`, `access(2)`.
- ["Writing a Simple Unix Shell in C"](https://www.google.com/search?q=writing+a+unix+shell+in+c) — general community tutorials on the classic
  fork/exec/pipe shell architecture.
- The 42 Minishell subject PDF itself, used throughout as the primary
  specification, with `bash` as the reference implementation for any
  unspecified edge case.
- Our dear friends that were very helpful : Simon Weinber

### AI usage

> _Fill this in honestly and specifically before submitting — evaluators will
> ask you to justify anything AI touched. Replace the placeholder text below
> with what you actually did._

AI tools (e.g. [tool name]) were used during this project for:
- *[task, e.g. "clarifying how `dup2` and pipe file descriptors interact
  across a multi-command pipeline"]*
- *[task, e.g. "reviewing my parser's handling of nested quotes for edge
  cases I hadn't considered"]*
- *[task, e.g. "explaining the difference between `waitpid` and `wait3`"]*

All AI-assisted explanations were cross-checked against the `bash`/`readline`
documentation and discussed with peers before being implemented; no code was
copy-pasted directly from AI output into the project without being fully
understood and rewritten where necessary, per the project's AI Instructions
(Chapter III of the subject).
