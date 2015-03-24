# 32-bits MIPS OS #

## Structure ##
This is an architecture sketch of our operating system. The operating system will contain eight main parts:

  1. Program execution
  1. Memory allocation
  1. Protection
  1. Scheduler
  1. I/O handling
  1. API/ System Calls
  1. Error detection
  1. Communications

### Program execution ###
This part of the operating system handles loading program into memory and running them. It
also handles the termination of these programs regardless of normal or abnormal termination.

### Memory allocation ###
This part will handle allocation of memory for the operating system, different user programs, the stack, etc. It keeps track of the available memory and makes sure we don't allocate already allocated memory.

### Protection ###
The protection part makes sure different processes doesn't interfere with each other or with the operating system itself when executing.

### Scheduler ###
The scheduler will choose programs to execute according to the, in the requirements specified, algorithm.

### I/O ###
I/O will handle the input from input devices (i.e. the keyboard) and output to output devices (i.e. the malta LCD and text to the console).

### API/System calls ###
The API will make several system calls available to user processes. These will allow the
processes to ask the operating system to perform privileged instructions, for instance fork.

### Error detection ###
Monitors the operating systems for errors, and in case of error sends an error signal to the process in which the error occurred.

### Communications ###
Handles communication between different processes using a pipe-like structure.