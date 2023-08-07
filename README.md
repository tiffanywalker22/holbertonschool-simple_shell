# Simple Shell

![image](https://github.com/tiffanywalker22/test/assets/121834519/77aefda3-ca99-4e00-bca9-b2f390d9873f)

<hr>

 ## Description 
<ul style=“list-style-type:square”> 
<li> Shell is a UNIX term for the interactive user interface with an operating system. </li>
<li> The shell is the layer of programming that understands and executes the commands a user enters. </li>
<li> In some systems, the shell is called a command interpreter. </li>
<li> This project is a simple version of the linux shell made for Holberton School </li> </ul> 

<hr>

## Files description
 - **AUTHORS** -> List of contributors to this repository
 - **man_1_simple_shell** -> Manual page for the simple_shell
 - **main.h** -> Header file
 - **main.c** -> Main function
   - **argv_path** -> Argv version of shell
   - **non_inter_path** -> Non-interative version of shell
   - **interactive_path** -> Interactive version of shell
- **forked.c** -> Creates processes
  - **fork_func** -> Forks functions
- **read_functions.c** -> Reads data
  - **get_input_inter** -> Gets input for interactive
  - **get_input_non_inter** -> Gets input from STDIN
  - **gettokens** -> Splits a string into tokens
  - **argv_tokenize** -> Removes first token from argv
- **processing_functions.c** -> Functions that run when called
  - **slash_processer** -> Takes input and removes bin to find command
  - **get_paths** -> Gets all potential paths
  - **check_dir** -> Checks the directory
  - **get_command** -> Returns commands and subcommands until second command appears
  - **tokenarraysub** -> Subtract tokens
- **exit_functions.c** -> Exiting the shell
  - **sigintCall** -> Calls the end of the function with control d or c
  - **normalExit** - Calls the end of the function with input "exit"
  - **execute_env** - Shows all environmental variables

<hr>

## Flowchart of our simple shell

![image](https://github.com/tiffanywalker22/holbertonschool-simple_shell/assets/121834519/cc210f34-3832-4474-afbb-ba4d9020a1c0)

<hr>

## How simple shell works
This code implements a basic shell program in C, allowing users to interactively enter commands or execute commands from a file through command-line arguments. It supports multiple execution modes: interactive, where the user inputs commands directly; non-interactive, where commands are read from a file or standard input; and command-line argument mode, where commands are passed as arguments. The program tokenizes user input into individual command tokens and searches for executable commands in specified paths. It uses fork to create child processes for command execution and utilizes the execve system call to run the requested commands. The program includes functions to handle signal interrupts, display environmental variables, and manage memory allocation. The overall structure encompasses input handling, command parsing, execution, and memory management to offer a simplified shell experience.

<hr>

## Requirements
<ul style=“list-style-type:square”>
<li> Allowed editors: vi, vim, emacs </li>
<li> All files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89 </li>
<li> All files should end with a new line </li>
<li> A README.md file, at the root of the folder of the project is mandatory </li>
<li> Code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl </li>
<li> Shell should not have any memory leaks </li>
<li> No more than 5 functions per file </li>
<li> All header files should be include guarded </li>
<li> Use system calls only when needed </li> </ul>

<hr>

## Authors
<a href="https://github.com/tiffanywalker22">Tiffany Walker</a> <br>
<a href="https://github.com/Zal-atan">Ethan Zalta</a> <br>


