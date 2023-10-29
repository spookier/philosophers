<div align=center>

# philosophers

</div>

philosophers is a project that explores the dining philosophers problem, a classic synchronization and concurrency problem

- this project is about multithreading and concurrency, focusing on the practical utilization of threads and mutexes

# Project Overview

- In this project, a number of philosophers are seated around a circular dining table, each pondering deep thoughts but occasionally pausing to eat from a bowl of spaghetti
- However, to eat, a philosopher needs to pick up two forks
- The challenge is to ensure that every philosopher gets a chance to eat without causing a deadlock or a race condition

# Technical Aspects

### Threads
- Threads are a way for a program to perform multiple tasks concurrently

In this project, each philosopher is represented by a thread

>The behavior of each philosopher (thinking, eating, sleeping) is implemented through thread operations

### Mutexes
- Mutexes are used to ensure that when one philosopher is picking up the forks, no other philosopher can pick up the same forks at the same time

>This is critical for avoiding race conditions and ensuring the correct program behavior

# Implementation Details

- Creating Philosophers: Each philosopher is created as a separate thread
- Handling Forks: Forks are shared resources, and their access is controlled using mutexes to ensure that only one philosopher can hold a fork at a time
- Eating, Sleeping, Thinking: The states of each philosopher are managed within their respective threads, ensuring they act independently but coordinate for shared resources

# Usage

```bash

./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_times_each_philosopher_must_eat]
```
# Tested with Helgrind
- Helgrind can detect three classes of errors:
  - Misuses of the POSIX pthreads API
  - Potential deadlocks arising from lock ordering problems
  - Data races -- accessing memory without adequate locking or synchronisation


> It's better to test this program with a natural flow of execution instead of stopping it with CTRL+C since this project does not include signal handling.
> In the example below, a philosopher should die
```
valgrind --tool=helgrind ./philo 3 310 200 200
```
![image](https://github.com/spookier/philosophers/assets/77325667/b2c0ce16-1e78-41f2-82ed-e22c18e54ee1)


