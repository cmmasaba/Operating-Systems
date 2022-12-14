# OPERATING SYSTEM CONCEPTS
Projects in this repository are part of the programming exercises and problems in the book Operating System Concepts.<br/>

## Technologies used
- `Compiler:` `gcc`
- `Environment:` `Ubuntu 22.04 LTS`

## Files
A description of the files contained in this project: <br/>
|**File**|**Description**|
|:---------------:|:--------------------|
|file_copy.c| a program that copies the contents of a source file to a destination file. Programming Problem 2.26|
|simple.c| creating `kernel modules`; Chapter2; Part I of programming projects on creating Linux Modules|
|shared_mem.c| a program showing how `shared memory` is used for IPC using the POSIX API |
|ordinary_pipe.c| a program that illustrates how to create and use `ordinary pipes` for client-server communication. Chapter 3 example|
|collatz_conjecture.c| a program that calculates the collatz conjecture of a number. The parent process creates a child process which does the calculation. Programming Problem 3.21 |
|collatz_shared_mem.c| a program that calculates the collatz conjecture, the parent process creates a child process which generates the sequence. Communication between the parrent process and child process is through `shared memory`. Programming Problen 3.22|
|reverse_case.c| a program that changes the cases of each letter in a string. The parent process and chile process communicate using` ordinary pipes`|
|filecopy.c| a program that copies the contents of one file to another file. The parent process creates a child process and uses `ordinary pipes` to send the contents of the sorce file to the child process, which then writes the contents to the destination file.|

## Usage
Clone the repository to your machine.
<br/>
### 1) Linux kernel modules
The Linux kernel module `simple.c` can be compiled using the Makefile that is provided along with the source code.<br/>
To compile the module enter the following command on the command line: <br/>
```C
make
```
Several files are produced after the compilation. The file `simple.ko` is the compiled kernel module.<br/>
The kernel module is loaded using the `insmod` command as follows:<br/>
```Bash
sudo insmod simple.ko
```
To check whether the module has been loaded, enter the `lsmod` command and search for the `simple` module in the output.<br/>
The module entry point in the file `simple.c` is invoked when the module is loaded. To check the contents of this message in the kernel log buffer, enter the command;<br/>
```Bash
dmesg
```
You should see the message `"Loading the module into the kernel"`. Alongside this there should also be messages showing details of the `birthday linked_list` structure.<br/>
Because the kernel buffer log fills up fast, it is often recommended to clear the contents of the log periodically. This can be accomplished by the command:<br/>
```Bash
sudo dmesg -c
```
To remove the kernel module, invoke the command `rmmod`<br/>
```Bash
sudo rmmod simple
```
Crosscheck using the `dmesg` command to ensure the kernel modules have been removed successfully.<br/>

## Contributors
Collins Mmasaba<br/>
`Email:` <collins.k.mmasaba@gmail.com><br/>
2022
