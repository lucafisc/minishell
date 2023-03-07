# Pipex

## Commands
### access
In Linux,  **_access_**  command is used to check whether the calling program has access to a specified file. It can be used to check whether a file exists or not. The check is done using the calling process’s real UID and GID.

int access(const char *pathname, int mode);

Here, the first argument takes the path to the  _directory/file_  and the second argument takes flags  _R_OK, W_OK, X_OK or F_OK_.

-   **F_OK flag**  : Used to check for existence of file.
-   **R_OK flag**  : Used to check for read permission bit.
-   **W_OK flag**  : Used to check for write permission bit.
-   **X_OK flag**  : Used to check for execute permission bit.

https://www.geeksforgeeks.org/access-command-in-linux-with-examples/

### dup and dup2
The **dup()** system call creates a copy of a file descriptor.

-   It uses the lowest-numbered unused descriptor for the new descriptor.
-   If the copy is successfully created, then the original and copy file descriptors may be used interchangeably.
-   They both refer to the same open file description and thus share file offset and file status flags.

**Syntax:**

    int dup(int oldfd);

**oldfd:** old file descriptor whose copy is to be created.

The **dup2()** system call is similar to dup() but the basic difference between them is that instead of using the lowest-numbered unused file descriptor, it uses the descriptor number specified by the user.  

**Syntax:**
int dup2(int oldfd, int newfd);
**oldfd:** old file descriptor
**newfd** new file descriptor which is used by dup2() to create a copy.

**Important points:**

-   Include the header file unistd.h for using dup() and dup2() system call.
-   If the descriptor newfd was previously open, it is silently closed before being reused.
-   If oldfd is not a valid file descriptor, then the call fails, and newfd is not closed.
-   If oldfd is a valid file descriptor, and newfd has the same value as oldfd, then dup2() does nothing, and returns newfd.

**A tricky use of dup2() system call:** As in dup2(), in place of newfd any file descriptor can be put. Below is a C implementation in which the file descriptor of Standard output (stdout) is used. This will lead all the printf() statements to be written in the file referred by the old file descriptor.

### execve
https://www.youtube.com/watch?v=iq7puCxsgHQ

The **_execXX()_** family is a set of system functions that are defined in the “unistd.h” header to run a process from within a program. This family of functions allows us to send the input arguments to the executable that calls it which is why it is a very useful resource for interaction between processes.

    int execv( const char *path, char *const argv[]);
The  **_execv()_**  function executes a process from another process or program. This function executes the file or executable which is specified in the  **_*path_**  argument. This entry should contain the absolute or relative path of the executable file in string format.

The  **_*argv[]_** argument is an array of pointers to strings where each string is an input argument that is passed to the process to be executed. The first pointer of the array should always point to a string that contains the name of the executable file and the last pointer should always be NULL. When  **_execv()_**  is called, the process from which it was called is terminated, rewritten, and replaced by the new process in the allocated portion of memory and with the same ID.

If the function is performed successfully, it does not return. If it returns, it is because an error occurs. The errors that this function can generate are varied, ranging from the non-existing executable file path to denied permissions.

> The calls with  `e`  in the name take an extra argument (or arguments
> in the  `l`  case) to provide the environment of the new program;
> otherwise, the program inherits the current process's environment.
> This is provided in the same way as the  `argv`  array: an array for 
> `execve()`, separate arguments for  `execle()`.

Execve does not inherit the environment variables! The environment variables are passed as a NULL-terminated array of strings to main as a third argument. But still the PATH is ignored.

### pipe()
Conceptually, a pipe is a connection between two processes, such that the standard output from one process becomes the standard input of the other process. In UNIX Operating System, Pipes are useful for communication between related processes(inter-process communication).

-   Pipe is one-way communication only i.e we can use a pipe such that One process write to the pipe, and the other process reads from the pipe. It opens a pipe, which is an area of main memory that is treated as a  **_“virtual file”_**.
-   The pipe can be used by the creating process, as well as all its child processes, for reading and writing. One process can write to this “virtual file” or pipe and another related process can read from it.
-   If a process tries to read before something is written to the pipe, the process is suspended until something is written.
-   The pipe system call finds the first two available positions in the process’s open file table and allocates them for the read and write ends of the pipe.
![](https://media.geeksforgeeks.org/wp-content/uploads/Process.jpg)

**Syntax**
int pipe(int fds[2]);
Parameters:
fd[0] will be the fd(file descriptor) for the 
read end of pipe.
fd[1] will be the fd for the write end of pipe.
Returns : 0 on Success.
-1 on error.
When we use [fork](https://www.geeksforgeeks.org/fork-system-call/) in any process, file descriptors remain open across child process and also parent process. If we call fork after creating a pipe, then the parent and child can communicate via the pipe.
![](https://media.geeksforgeeks.org/wp-content/uploads/sharing-pipe.jpg)

### fork()
Fork system call is used for creating a new process, which is called  **_child process_**, which runs concurrently with the process that makes the fork() call (parent process). After a new child process is created, both processes will execute the next instruction following the fork() system call. A child process uses the same pc(program counter), same CPU registers, same open files which use in the parent process.

It takes no parameters and returns an integer value. Below are different values returned by fork().

**_Negative Value_**: creation of a child process was unsuccessful.  
**_Zero_**: Returned to the newly created child process.  
**_Positive value_**: Returned to parent or caller. The value contains process ID of newly created child process.

    #include <stdio.h>
    #include <sys/types.h>
    #include <unistd.h>
    int main()
    {
    	// make two process which run same
    	// program after this instruction
    	fork();
    	printf("Hello world!\n");
    	return 0;
    }
Output:

    Hello world!
    Hello world!

fork() **returns** 0 for the child process and a positive integer for the parent, so we can distinguish in which project we are checking conditionally the return value.
**Important:** Parent process and child process are running the same program, but it does not mean they are identical. OS allocate different data and states for these two processes, and the control flow of these processes can be different.
### unlink()
**unlink**() deletes a name from the filesystem.  If that name was the last link to a file and no processes have the file open, the file is deleted and the space it was using is made available for reuse.

If the name was the last link to a file but any processes still have the file open, the file will remain in existence until the last file descriptor referring to it is closed.
If the name referred to a symbolic link, the link is removed.
If the name referred to a socket, FIFO, or device, the name for it is removed but processes which have the object open may continue to use it.
On success, zero is returned.  On error, -1 is returned, and _[errno](https://man7.org/linux/man-pages/man3/errno.3.html)_ is set to indicate the error.
## General notions

> The **Portable Operating System Interface** (**POSIX**) is a family of
> [standards](https://en.wikipedia.org/wiki/Standardization
> "Standardization") specified by the [IEEE Computer
> Society](https://en.wikipedia.org/wiki/IEEE_Computer_Society "IEEE
> Computer Society") for maintaining compatibility between [operating
> systems](https://en.wikipedia.org/wiki/Operating_system "Operating
> system").[[1]](https://en.wikipedia.org/wiki/POSIX#cite_note-FAQ-1)
> POSIX defines both the system and user-level [application programming
> interfaces](https://en.wikipedia.org/wiki/Application_programming_interface
> "Application programming interface") (APIs), along with command line
> [shells](https://en.wikipedia.org/wiki/Unix_shell "Unix shell") and
> utility interfaces, for software compatibility (portability) with
> variants of [Unix](https://en.wikipedia.org/wiki/Unix "Unix") and
> other operating
> systems.[[1]](https://en.wikipedia.org/wiki/POSIX#cite_note-FAQ-1)[[2]](https://en.wikipedia.org/wiki/POSIX#cite_note-IET-2) POSIX is also a [trademark](https://en.wikipedia.org/wiki/Trademark
> "Trademark") of the
> IEEE.[[1]](https://en.wikipedia.org/wiki/POSIX#cite_note-FAQ-1) POSIX
> is intended to be used by both application and system developers.


[Practical use case for fork and pipe in C (Code Vault)](https://www.youtube.com/watch?v=6u_iPGVkfZ4)
[Simulating the pipe "|" operator in C (Code Vault)](https://www.youtube.com/watch?v=6xbLgZpOBi8)

## Workflow

What I need to successfully do the project (with bonus) is:
- A pipe for every two commands
- A fork for every command
- A good redirection with dup2 to have the right input going into the first command and the right output coming out of the last
- The command I pass to execve needs to be executable, which means in most cases adding its path (for `cat` I should pass `/usr/cat` and so on).

I thought to do with less forks but I wasn't able and I'm not sure it would work anyway... The child of the fork is the one executing the command.
The trickiest bit is making sure that all the "loose ends" of the pipes are closed otherwise the program will hang waiting for more more to be read or to be written. The first command needs to read from the given infile, the last command needs to write to the given outfile.
If the command I got parsing the args is not executable, I look for the PATH= variable in the environment (the environment is always silently passed to main as a null-terminated array of strings), split its value by ':' and join each path to the command to test again if its executable (`access(my_command, X_OK`). When I find it I can pass it to execve.

