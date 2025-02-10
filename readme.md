# PROJECT PHILOSOPHERS FOR 42
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

**Note that the libft is forbidden!**

**Also note that philo and philo_bonus each have their own makefile in their own directory!**

### BONUS PART:

The program for the bonus part takes the same arguments as the mandatory program
and must comply with the requirements of the Global rules chapter.
In the bonus part, all forks are placed in the middle of the table
They do not have individual states in memory, and the number of available forks is represented by a semaphore.
Each philosopher should be implemented as a process, but the main process should not act as a philosopher.

### ABOUT MY PROJECT:

For this project, I chose to reuse the doubly circular linked list functions I had created for the push_swap project, but I made them generic functions. These functions use a structure that can be applied to any project, containing only:
- a pointer to next
- a pointer to previous
- a pointer to void *data, allowing it to accept any type of data
Of course, this isn't the simplest choice (an array of structures would be sufficient), but I wanted to take advantage of this project to refine my doubly circular linked list functions, which I plan to integrate directly into my libft later on.

## SOME COMMANDS YOU CAN USE:

compile the program and suppress the .o files:

	make && make clean

execute the program (you must pass 4 or 5 arguments)

	./philo <number_of_philosophers> <time_to_die in milliseconds> <time_to_eat in milliseconds> <time_to_sleep in milliseconds> <optional: number_of_times_each_philosopher_must_eat>

 for example: execute the program with 6 philosophers, 500 ms to die, 200 ms to eat, 200 ms to sleep, and the program stops when each philosopher has eaten 5 times

	./philo 6 500 200 200 5

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


It is essential to wait for the completion of each thread before terminating a program to ensure proper resource management and program stability.
Failing to do so may lead to resource leaks, incomplete operations, or corrupted data if a thread is prematurely interrupted while accessing shared resources.
Synchronization functions like pthread_join() in POSIX threads allow the main thread to wait for specific threads to finish execution, guaranteeing that all necessary tasks are completed before program termination.
This practice also prevents creating orphaned threads, which continue to run in the background and consume system resources unnecessarily.
Properly managing thread lifecycle ensures robust and predictable program behavior.

---

### timestamp
A timestamp is a sequence of characters representing the date and time when a specific event occurred. It is typically formatted as a combination of year, month, day, hour, minute, and second, often in a standard format like UNIX time (the number of seconds since January 1, 1970, UTC). Timestamps are widely used in computing to track events, synchronize processes, and manage time-sensitive operations such as logging, file modifications, and database entries.

---

### gettimeofday()
> #include <sys/time.h>

	int gettimeofday(struct timeval *tv, struct timezone *tz);

The gettimeofday function retrieves the current time since the UNIX epoch (January 1, 1970, 00:00:00 UTC) with microsecond precision.

Arguments:
- a pointer to a struct timeval, where seconds (tv_sec) and microseconds (tv_usec) are stored
- an optional struct timezone parameter, which is usually set to NULL as it is obsolete

The function returns 0 on success or -1 on failure.
It is commonly used to measure elapsed time or add precise timestamps to logs.
While it provides microsecond precision, the actual accuracy depends on the system.
For higher precision or monotonic timing, clock_gettime is a better alternative.

### timeval structure
The timeval structure is used to represent a specific point in time with precision up to microseconds.
It contains two fields:
- tv_sec, which stores the number of seconds since the UNIX epoch (January 1, 1970)
- tv_usec, which stores the remaining time in microseconds (ranging from 0 to 999999)

This structure is commonly used with functions like gettimeofday to retrieve the current time or calculate time intervals.
It provides a simple way to represent high-resolution timestamps,
but for some applications, alternative structures or functions may offer more features or higher precision.

---

### pthread_create()
> #include <pthread.h>

	int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);

pthread_create() is used to create a new thread in a program.
It allows the execution of a function concurrently with the main thread.
The function takes four arguments:
- a pointer to a pthread_t variable, where the thread ID will be stored
- an optional pointer to a pthread_attr_t structure to specify thread attributes, or NULL for default attributes
- a pointer to the function that the thread will execute
- a pointer to the argument that will be passed to the function.

The function returns 0 on success and a positive error code on failure.

### pthread_attr_t structure
The pthread_attr_t structure is used to specify attributes for a thread when creating it with pthread_create().
It allows you to customize various aspects of the thread's behavior, such as
its stack size, scheduling policy, and whether it is joinable or detached.
By default, if pthread_attr_t is set to NULL in pthread_create, the thread will be created with the system's default attributes.
The attributes that can be set using this structure include:
- Stack size: The amount of memory allocated for the thread’s stack
- Scheduling policy: Defines how the thread is scheduled by the system (e.g., SCHED_FIFO, SCHED_RR, or SCHED_OTHER)
- Scheduling priority: A priority value that can affect the scheduling of the thread
- Detached or joinable: Whether the thread is joinable (can be waited on by other threads) or detached (resources are automatically freed when it finishes)
- Scope of the thread: Determines whether the thread's execution is bound to a processor (for systems with processor affinity)

To set these attributes, the pthread_attr_t structure must be initialized using pthread_attr_init() and can be modified using other functions like pthread_attr_setstacksize(), pthread_attr_setschedpolicy(), etc. Once the thread is created, the attributes are not used again, and modifying them after creation does not affect the already created thread.

---

### pthread_detach()
> #include <pthread.h>

	int pthread_detach(pthread_t thread);

pthread_detach() is used to detach a thread, meaning it will run independently and its resources will be automatically released once it finishes execution.
This function prevents the need for another thread to call pthread_join() to clean up the detached thread.
It is typically used when you do not need to wait for a thread to finish or retrieve its result.
The argument is the thread identifier (pthread_t) of the thread to be detached.
The function returns 0 on success and a positive error code on failure.

---

### pthread_join()
> #include <pthread.h>

	int pthread_join(pthread_t thread, void **retval);

pthread_join() is used to make the calling thread wait for a specified thread to finish execution.
It allows the caller to optionally retrieve the return value of the joined thread.
The arguments are
- the thread identifier (pthread_t) of the thread to wait for
- a pointer to a variable where the return value of the thread can be stored (or NULL if not needed).
The function returns 0 on success and a positive error code on failure, such as if the thread is already detached or invalid.

---

### mutex
A mutex (short for "mutual exclusion") is a synchronization primitive used to prevent multiple threads from accessing shared resources simultaneously,
which could lead to data corruption or inconsistency.
It ensures that only one thread can enter a critical section of code at a time,
while other threads that try to access the same section are blocked until the mutex is released.

The basic operation of a mutex involves two main functions:
- Locking (pthread_mutex_lock):
A thread must lock the mutex before entering the critical section.
If the mutex is already locked by another thread, the requesting thread will be blocked until the mutex becomes available.
- Unlocking (pthread_mutex_unlock):
After the thread finishes its work in the critical section, it must unlock the mutex, allowing other threads to access the resource.

In addition to these basic operations, there are other features, such as trylock (which allows a thread to attempt locking a mutex without blocking) and deadlock prevention (by ensuring that mutexes are unlocked properly).

Mutexes are often used to protect shared data structures or resources in multithreading programs to maintain data integrity. However, improper use of mutexes can lead to issues like deadlocks, where two or more threads are waiting for each other to release a mutex, causing the program to freeze.


Properly unlocking and destroying all mutexes before terminating a program is crucial to maintain resource integrity and ensure system stability.
If mutexes remain locked, other threads may be indefinitely blocked, leading to deadlocks and resource leaks.
Unlocking mutexes allows all waiting threads to complete their operations, while calling pthread_mutex_destroy() ensures that system resources associated with the mutex are released.
Failure to destroy mutexes can result in memory leaks and undefined behavior, especially in long-running or resource-intensive applications.
Cleaning up mutexes properly is a best practice in multithreaded programming for robust and predictable program execution.

---

### pthread_mutex_init()
> #include <pthread.h>

	int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);

pthread_mutex_init() is used to initialize a mutex.
The function takes two arguments:
- a pointer to a pthread_mutex_t variable, which will hold the initialized mutex
- an optional pointer to a pthread_mutexattr_t structure to define custom attributes for the mutex (or NULL for default attributes)
The function returns 0 on success and a positive error code on failure.

---

### pthread_mutexattr_t structure
The pthread_mutexattr_t structure is used to define the attributes of a mutex in POSIX threading.
It allows customization of mutex behavior, such as setting its type (e.g., normal, recursive, or error-checking) or defining its process-shared behavior.
The structure is opaque, meaning its internal variables are not directly accessible by programmers, and it is managed by the POSIX library implementation.
However, the attributes can be modified through specific functions such as pthread_mutexattr_settype() and are used to define the behavior of the mutex.
The main attributes include the mutex type
(e.g., PTHREAD_MUTEX_NORMAL, PTHREAD_MUTEX_RECURSIVE, PTHREAD_MUTEX_ERRORCHECK, and PTHREAD_MUTEX_DEFAULT)
and process-sharing options
(PTHREAD_PROCESS_PRIVATE for use within the same process and PTHREAD_PROCESS_SHARED for sharing between processes).
These attributes are configured using functions like pthread_mutexattr_init(), pthread_mutexattr_settype(), and pthread_mutexattr_setpshared().
Although the structure itself cannot be directly examined, its attributes can be modified using the available API functions.
The structure is typically initialized using pthread_mutexattr_init() and can be modified with functions like pthread_mutexattr_settype().

---

### pthread_mutex_destroy()
> #include <pthread.h>

	int pthread_mutex_destroy(pthread_mutex_t *mutex);

pthread_mutex_destroy() is used to destroy a previously initialized mutex.
After a mutex is destroyed, it can no longer be used, and its resources are released.
The function takes a pointer to a pthread_mutex_t variable that identifies the mutex to be destroyed.
It is important to ensure that no thread is holding the mutex when calling pthread_mutex_destroy, as this could result in undefined behavior.
The function returns 0 on success and a positive error code on failure.

---

### pthread_mutex_lock()
> #include <pthread.h>

	int pthread_mutex_lock(pthread_mutex_t *mutex);

pthread_mutex_lock() is used to lock a mutex, ensuring that only one thread can access a critical section at a time.
If the mutex is already locked by another thread, the calling thread will be blocked until the mutex becomes available.
The function takes a pointer to a pthread_mutex_t variable, which represents the mutex to be locked.
The function returns 0 on success and a positive error code on failure, such as when the mutex is invalid or already locked.

---

### pthread_mutex_unlock()
> #include <pthread.h>

	int pthread_mutex_unlock(pthread_mutex_t *mutex);

pthread_mutex_unlock is used to unlock a previously locked mutex, allowing other threads to access the critical section that was protected by the mutex. The function takes a pointer to a pthread_mutex_t variable, which represents the mutex to be unlocked. It is important that the thread calling this function has previously locked the mutex. The function returns 0 on success and a positive error code on failure, such as when the mutex is not locked by the calling thread.

---

### the creation of processes
> Fom a quick introduction to processes, see the readme of my minitalk project on github:
> https://github.com/donnatchris/minitalk

The creation of processes is a fundamental aspect of managing multitasking applications on modern operating systems.
A process represents a program in execution, with its own memory space, address space, and resources.
When a program wants to execute a parallel task or a subtask, it can create a new process by duplicating the calling process, which is exactly what the fork() function does.
This mechanism allows creating independent processes that can run in parallel.

#### differences between fork() and thread creation
The differences between fork() and thread creation are mainly related to how processes and threads manage execution, memory, and resources.
fork() creates a new, independent process with its own memory space, file descriptors, and execution context.
The child process is a copy of the parent at the time of creation, but after fork() is called, the two processes run independently.
In contrast, a thread creates an execution unit within the same process, sharing the same memory space and resources as the main thread.
Threads are lighter than processes and share a common execution environment.


When fork() is called, each process (parent and child) has its own separate memory after the fork() call.
However, before fork() is executed, the two processes share memory, but once fork() is called, changes made in one do not affect the other (except for optimizations like "copy-on-write").
Threads, on the other hand, share the same memory, including global variables and resources. This can make memory management more complex because synchronization mechanisms like mutexes must be used to avoid concurrent access conflicts.

The child process created with fork() inherits the file descriptors and other resources from the parent, but it can modify them independently.
Each process can also have its own system resources, like process IDs. In contrast, all threads in a process share the process's resources, such as memory and file descriptors.
They have distinct thread IDs, but the other resources are shared.


Creating a new process with fork() is more costly in terms of time and resources because it involves duplicating the parent process.
In contrast, creating a thread is generally less costly than creating a process because there is no full duplication of memory and resources; only a new execution environment is added to the existing process.


The parent and child processes created with fork() run independently.
They can continue their work without blocking each other, but each process has its own execution context.
Threads run concurrently in the same process and can easily share data, but they must be synchronized correctly to avoid issues like race conditions.


When the child process terminates after a fork(), it does not terminate the parent process.
Both processes can continue running independently, and the termination of child processes must be managed using wait() or waitpid() in the parent.
When a thread finishes execution, the main process does not necessarily terminate, but it must ensure that all threads have finished before exiting.
The process waits for all threads to finish before closing.


Communication between processes with fork() is generally done using IPC (Inter-Process Communication) mechanisms, such as pipes, message queues, or shared memory.
This involves more complex mechanisms than for threads, where communication between threads can be done using shared variables.
However, this requires synchronization to avoid conflicts from concurrent access.


fork() allows parallel execution between the parent and the child.
Each process can run on a separate processor in multi-processor systems.
Threads also allow parallel execution, but all threads run within the same memory space, making them lighter but potentially more prone to synchronization issues.


In summary, fork() creates a new process with its own memory and resources, more costly in terms of time and management, and typically used for independent tasks. Threads create an execution unit within the same process, sharing memory and resources, lighter but requiring synchronization mechanisms to avoid issues related to concurrent data access. Each method has its advantages and disadvantages depending on the needs of the application (parallelism, data sharing, resource cost, etc.).


To properly terminate a child process using waitpid() and exit(), start by creating the child process with fork().
The parent and child continue executing their respective code after the fork.

In the child process, perform the necessary tasks.
Call exit(status) to terminate properly.
The status is an integer value, often EXIT_SUCCESS or EXIT_FAILURE, which will be returned to the parent.

In the parent process, use waitpid() to wait for the child process to finish and retrieve its exit status.
Check if the child terminated normally with the WIFEXITED(status) macro and get the exit status using WEXITSTATUS(status).

---

### fork()
> #include <unistd.h>

	pid_t fork(void);
 
The fork() function creates a new process by duplicating the calling process.
It is available on Unix and Unix-like systems.
The newly created process, called the child process, operates independently from the parent process.


When fork() is called, a new child process is created.
The child process inherits the memory, file descriptors, and execution context of the parent process.
Both processes continue execution from the instruction following the fork() call.
They can perform different tasks based on conditions defined after the fork().

#### Return values
- In the parent process, fork() returns the child process identifier (a positive integer).
- In the child process, fork() returns 0.
- In case of an error (failure to create the process), fork() returns -1 and sets errno (needs stdio.h for errno).

#### Practical use cases
- Concurrent servers: fork() is used to handle multiple clients simultaneously, with each client managed by a separate child process.
- Parallel processing: It allows the distribution of intensive computations across multiple processes to improve performance.
- Shells like bash: When a command is executed, the shell creates a child process with fork() to run the command while keeping the parent process available.
- Pipeline management (ls | grep): Each command in the pipeline is executed in a separate process created with fork().

---

### waitpid()
> #include <sys/types.h>

> #include <sys/wait.h>

	pid_t waitpid(pid_t pid, int *status, int options)
 

The waitpid() function is used to wait for the termination of a specific child process and retrieve its termination status.
Unlike wait(), which waits for any child process, waitpid() allows targeting a specific child.
The pid parameter specifies which process to wait for.
- A value greater than 0 waits for the process with the specified identifier.
- A value of -1 is equivalent to wait(), waiting for any child process.
- A value of 0 waits for a child process from the same process group as the parent.
- A value less than -1 waits for a child whose process group matches the absolute value of pid.
  
The status parameter is a pointer to an integer variable used to store the termination status of the child process.
Macros like WIFEXITED(status) can be used to interpret this status.
The options parameter allows adjusting the function's behavior.
A value of 0 indicates the default behavior, blocking the parent until the child process terminates.
The WNOHANG option prevents blocking if no child process has terminated. The WUNTRACED option reports child processes that have been stopped but not terminated.
The function returns the pid of the terminated process if it succeeds.
If no condition is met and WNOHANG is used, it returns 0.
In case of an error, it returns -1 and sets errno.

---

### semaphores

Semaphores are synchronization primitives used in concurrent programming to control access to shared resources. They are counters that help manage how many threads or processes can access a critical section at the same time. There are two main types of semaphores: binary semaphores, which act like simple locks allowing only one thread at a time, and counting semaphores, which allow a specified number of threads or processes to access the resource simultaneously.

The basic operations of semaphores are wait (often called P or sem_wait) and signal (also called V or sem_post). The wait operation decrements the semaphore and may block the calling thread if the semaphore value is zero, indicating that the resource is fully occupied. The signal operation increments the semaphore, potentially unblocking a waiting thread. Semaphores are particularly useful for synchronizing processes in multi-threaded or multi-process environments, preventing race conditions and ensuring data integrity.

---

### sem_open()

> #include <semaphore.h>

	sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);

sem_open() is a function used to create or open named semaphores, which are semaphores accessible across different processes.
Named semaphores are identified by a unique string name and are particularly useful when processes need to synchronize without sharing memory directly.

The sem_open() function accepts the following parameters:
- const char *name: A string that uniquely identifies the named semaphore.
The name must start with a / followed by alphanumeric characters, such as "/my_semaphore".
- int oflag: Specifies the action to perform.
O_CREAT creates the semaphore if it does not already exist.
O_EXCL causes an error if O_CREAT is used and the semaphore already exists.
- mode_t mode (optional): Used only if O_CREAT is specified.
It defines the access permissions for the semaphore according to standard Unix values (for example, 0666 for read/write permissions for all users).
- unsigned int value (optional): Used only if O_CREAT is specified.
It sets the initial value of the semaphore (the counter for available resources).

sem_open() returns a pointer to the semaphore object if successful, or SEM_FAILED on error.
Once finished, it's important to close the semaphore with sem_close() and unlink it with sem_unlink() to release system resources.
