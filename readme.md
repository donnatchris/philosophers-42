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

NOTE THAT THE LIBFT IS FORBIDEN!

ALSO NOTE THAT philo AND philo_bonuS EACH HAVE THEIR OWN MAKEFILE IN THEIR OWN DIRECTORY

### BONUS PART:

The program for the bonus part takes the same arguments as the mandatory program
and must comply with the requirements of the Global rules chapter.
In the bonus part, all forks are placed in the middle of the table
They do not have individual states in memory, and the number of available forks is represented by a semaphore.
Each philosopher should be implemented as a process, but the main process should not act as a philosopher.

## SOME COMMANDS YOU CAN USE:

compile the program and clean by suppressinf the .o files:

	make & make clean

execute the program (you must pass 4 or 5 arguments)

	./philo <number_of_philosophers> <time_to_die in milliseconds> <time_to_eat in milliseconds> <time_to_sleep in milliseconds> <optional: number_of_times_each_philosopher_must_eat>

 for example: execute the program with 5 philosophers, 500 ms to die, 500 ms to eat, 500 ms to eat, 500 ms to sleep, and the program stops when eash philosopher has eaten 100 times

	./philo 500 500 500 500 100

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

### Timeval structure
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
