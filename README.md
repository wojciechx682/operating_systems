# operating_systems

show_process_linux.sh

    This is a Bash script that performs various operations related to processes running on a Linux system. The script uses the /proc virtual file system to gather information about processes.

    The first part of the script lists all currently running processes and saves their names to a file named file. The ls /proc command lists the contents of the /proc directory, which includes a subdirectory for each running process, and the grep -E [0-9] command filters out any non-process directories. The resulting process directories are then sorted numerically using the sort -g command and saved to the file file.

    The second part of the script reads the file file into an array called pid. If the script is called with the -p parameter, it prints various information about each process. The script loops over each element of the `pid arrayppid),uid), usernameuname),pname)/proc file

    If-u parameterwhoami command/proc filefile_user.pid2 and loops over each element of the array to print various information about each process, including its parent process ID (ppid), process name (pname), and current working directory (katalog_roboczy).

    If the script is called with no parameters or with an invalid parameter, it prints an appropriate error message. Finally, the script removes the file and file_user files, if they were created during execution.
    
create_process_linux.c

    C program that takes an integer argument from the command line and performs a recursive operation. The program checks the validity of the input argument and recursively calls itself twice with the argument decremented by 1 and 2, respectively. It then waits for the two child processes to finish executing and returns the sum of their return values.

    The program also prints the process ID, parent process ID, input argument, and return value of each child process. If the input argument is not a natural number or is outside the range of 1 to 13, the program returns an error code.
