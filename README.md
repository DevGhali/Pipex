<h1> Pipex (|) </h1>
</br>

Pipex is a program that mimics the functionality of the shell pipeline (|).
<img width="300" height="250" align="right" src="https://user-images.githubusercontent.com/113459534/227326275-6968e417-c73e-4e2b-ad3b-f2d9df554572.jpeg"/>

It takes two commands as arguments and creates a pipe between them, so that the output of the first command becomes the input of the second command. example below 👇👇👇
</br>
</br>
> The program will be executed as follows :

```bash
./pipex file1 cmd1 cmd2 file2
```
> And should behave like this in the ordinary shell :
```bash
< file1 cmd1 | cmd2 > file2 
```
</br>
Now here is a visual breakdown of the command and an example for every element of the command :
</br>
</br>
<img width="1000" height="700" src="https://user-images.githubusercontent.com/113459534/227591534-22839aaa-d0cd-49d7-a496-cff18d2830f4.jpg"/>

## Concepts introduced in this project 🔮
- [Pipes in Linux](https://www.liquidweb.com/kb/how-to-use-linux-pipe-for-redirection/#:~:text=A%20pipe%20is%20a%20form,placed%20between%20any%20two%20commands.) - Here you will find information on pipes and what do they do which is basically what the whole projet is about.
- [Processes - Child/Parent Processes](https://www.geeksforgeeks.org/difference-between-process-parent-process-and-child-process/) - Running a program means running a process and with so two new processes will be created a Parent process and a Child process and what is the Child process for?? you might ask... imagine we want to run two jobs simultaneously and that can be achieved with the help of Parent/Child processes.
- [Linux path environment variable](https://linuxconfig.org/linux-path-environment-variable) - Environmental paths in Linux and why do we need them, mainly when we run a command in the terminal, how does it know where to find the program and execute it? with the help of the 'PATH' variable the system can locate the program's path and execute it. but before we try to execute we need to check if we have permission to execute the program, check the next point below 👇
- [The access() function in C](https://www.informit.com/articles/article.aspx?p=23618&seqNum=3#:~:text=The%20access%20system%20call%20determines,access%20call%20takes%20two%20arguments.) - The access() function is a system call used to check wether the calling process has permissions to a file.
- [Printing system errors](https://man7.org/linux/man-pages/man3/perror.3.html) - Whenever an error has occured during one of the system calls, the system should print an error to the Standard Error Stream (STDERR) with a descriptive message describing the error.

## Functions introduced in this project 🔮
- open() -  The open() function shall establish the connection between a file and a file descriptor.
- pipe() -  pipe() creates a pipe, a unidirectional data channel that can be used for interprocess communication.
- fork() -  fork() creates a new process by duplicating the calling process.
- waitpid() - system call used to wait for state changes in a child of the calling process, and obtain information about the child whose state has changed
- access()  - check real user's permissions for a file.
- dup2() -  duplicate a file descriptor.
- close() - close() closes a file descriptor, so that it no longer refers to any file and may be reused.
- execve() -  execute program.
- perror() -  print a system error message.
- exit() -   cause normal process termination.

## Diagram on how the function works 📊
<img src="https://user-images.githubusercontent.com/113459534/227723305-02700bfb-dcd6-433c-85f9-3ed648d369e5.jpg"/>

-  [The dup2() function](https://www.ibm.com/docs/en/i/7.3?topic=ssw_ibm_i_73/apis/dup2.html) - basically it duplicates a file discriptor to another for instance : dup2(int fd1,int fd2) closes fd2 and duplicates the value of fd2 to fd1 so that fd1 becomes fd2.


## BONUS Part ✚
The bonus part brings 2 major improvements to the project, 1. that it can handle multiple commands and not be limited to only 2 commands like in the mandatory part, multiple commands means multiple pipes.
> as follows :
```bash
./pipex file1 cmd1 cmd2 cmd3 cmd4 ... cmdn file2
```
> Should behave like (how the original command would look like in the ordinary shell) :
```bash
< file1 cmd1 | cmd2 | cmd3 | cmd4 ... cmdn > file2
```


2. Support << and >> in other words ["heredoc"](https://linuxize.com/post/bash-heredoc/), im not gonna explain heredoc in details you can give it a look :)
> as follows :
```bash
./pipex heredoc LIMITER cmd1 cmd2 file
```
> Should behave like (how the original command would look like in the ordinary shell) :
```bash
cmd1 << LIMITER | cmd1 >> file
```

## Usage
> compile using the Makefile :

```bash
make all
```

> for bonus :

```bash
make bonus
```

> create the infile/outfile :
```bash
make files
```
> run the program : 
```bash
./pipex infile 'cmd1' 'cmd2' outfile
```
