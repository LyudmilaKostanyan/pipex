# Pipex

The Pipex project at 42 School is a programming assignment that focuses on understanding and implementing Unix processes, pipes, and file descriptors. It's a typical second circle project that builds on foundational C programming skills and knowledge of system calls. Here's a brief overview:

### Objectives:
- To understand and implement inter-process communication using pipes.
- To manipulate file descriptors to redirect input and output.
- To handle multiple processes using `fork()`, `exec()`, and related system calls.

### Project Requirements:
- **Basic Setup**: The project usually involves creating a program that mimics the behavior of the shell command `|` (pipe). For example, executing `./pipex file1 cmd1 cmd2 file2` should have the same effect as `cat file1 | cmd1 | cmd2 > file2` in the shell.
- **Error Handling**: The program should handle various errors gracefully, such as incorrect usage, failure of system calls, and invalid commands.
- **File Management**: It should correctly manage file descriptors to read from and write to files specified in the command-line arguments.

### Key Concepts:
1. **Pipes**: Pipes are used to pass the output of one process to another as input.
2. **Fork**: The `fork()` system call is used to create a new process.
3. **Exec**: The `exec` family of functions replaces the current process image with a new process image.
4. **Dup2**: The `dup2()` system call is used to duplicate file descriptors, which is crucial for redirecting input and output.

### Implementation Steps:
1. **Parsing Arguments**: The program needs to parse command-line arguments to understand the file names and commands to be executed.
2. **Creating Pipes**: Use the `pipe()` system call to create a pipe for inter-process communication.
3. **Forking Processes**: Use `fork()` to create child processes for each command to be executed.
4. **Redirecting I/O**: Use `dup2()` to redirect standard input and output to the appropriate file descriptors.
5. **Executing Commands**: Use `execve()` or a similar function to execute the commands.
6. **Handling Errors**: Implement robust error handling to manage possible failures in system calls.

