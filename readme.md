#PROJECT PHILOSOPHERS FOR 42
By chdonnat (Christophe Donnat from 42 Perpignan, France)

## AIM OF THE PROJECT:

The program(s) should take the following arguments:
- number_of_philosophers,
which is the number of philosophers and forks
- time_to_die in milliseconds,
which is the time a philosopher can go without eating since their last meal or the simulation start before they die
- time_to_eat in milliseconds,
which is the time it takes for a philosopher to eat, during which they must hold two forks
- time_to_sleep in milliseconds,
which is the time a philosopher spends sleeping
- number_of_times_each_philosopher_must_eat,
which is optional and specifies that
if all philosophers have eaten this many times, the simulation stops
If this argument is not provided, the simulation stops when a philosopher dies.

Each philosopher has a number from 1 to number_of_philosophers. Philosopher number 1 sits next to philosopher number number_of_philosophers.

Logs of the program must show any state change of a philosopher in the following format: timestamp_in_ms X has taken a fork, timestamp_in_ms X is eating, timestamp_in_ms X is sleeping, timestamp_in_ms X is thinking, or timestamp_in_ms X died. Replace timestamp_in_ms with the current timestamp in milliseconds and X with the philosopher’s number. A state message should not overlap with another, and a death message must appear no later than 10 milliseconds after the philosopher’s actual death.

Philosophers should avoid dying. Philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.

Specific rules for the mandatory part include that each philosopher should be a thread. There is one fork between each pair of philosophers, meaning that if there are several philosophers, each has a fork on their left and right sides. If there is only one philosopher, there is only one fork on the table. Fork states must be protected with a mutex to prevent duplication.

NOTE THAT THE LIBFT IS FORBIDEN!

### BONUS PART:

The program for the bonus part takes the same arguments as the mandatory program
and must comply with the requirements of the Global rules chapter.
In the bonus part, all forks are placed in the middle of the table
They do not have individual states in memory, and the number of available forks is represented by a semaphore.
Each philosopher should be implemented as a process, but the main process should not act as a philosopher.

## SOME COMMANDS YOU CAN USE:

compile the program:

	make

execute the program (you must pass a file containing coordonates)

	./fdf <file>

## ARCHITECTURE:

- philo/ directory with files for the mandatory part
	- src/ directory for main files of the project
	- utils/ directory for secondary files
	- include/ directory for headers
- philo_bonus/ directory with files for the bonus part
	- src/ directory for main files of the project
	- utils/ directory for secondary files
	- include/ directory for headers
- test/ directory fot tests files
- Makefile (with rules: make bonus clean fclean re)
- readme.md for quick explanation and main commands of the project

## DOCUMENTATION:

### thread
A thread is a single unit of execution within a process.
It allows a program to perform multiple tasks concurrently, sharing the same memory space and resources (such as file descriptors) as the parent process.
Each thread has its own execution context, including a program counter, stack, and local variables, but it shares global variables with other threads in the same process.
Threads are commonly used to improve the performance of applications by performing operations like I/O, computation, or waiting for events in parallel, without blocking the main execution flow of the program.
Multiple threads within the same process are often referred to as multithreading, which can lead to more efficient use of system resources, especially on multi-core processors.

Fom more explanation about processes, see the readme of my minitalk project on github:
https://github.com/donnatchris/minitalk

---

### gettimeofday()
#include <sys/time.h>

int gettimeofday(struct timeval *tv, struct timezone *tz);

The gettimeofday function retrieves the current time since the UNIX epoch (January 1, 1970, 00:00:00 UTC) with microsecond precision.
#### Arguments:
- a pointer to a struct timeval, where seconds (tv_sec) and microseconds (tv_usec) are stored
- an optional struct timezone parameter, which is usually set to NULL as it is obsolete

The function returns 0 on success or -1 on failure.
It is commonly used to measure elapsed time or add precise timestamps to logs.
While it provides microsecond precision, the actual accuracy depends on the system.
For higher precision or monotonic timing, clock_gettime is a better alternative.

### Timeval structure
The timeval structure is used to represent a specific point in time with precision up to microseconds.
It contains two fields:
- tv_sec, which stores the number of seconds since the UNIX epoch (January 1, 1970)
- tv_usec, which stores the remaining time in microseconds (ranging from 0 to 999999)

This structure is commonly used with functions like gettimeofday to retrieve the current time or calculate time intervals.
It provides a simple way to represent high-resolution timestamps,
but for some applications, alternative structures or functions may offer more features or higher precision.

