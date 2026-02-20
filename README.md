*This project has been created as part of the 42 curriculum by **jkarippa**.*

# Philosophers

## Description

The **Philosophers** project is an implementation of the classical *Dining Philosophers Problem*, a well-known concurrency and synchronization problem in computer science.

The goal of this project is to simulate a group of philosophers sitting around a table who alternately eat, sleep, and think. To eat, each philosopher must hold two forks — one on their left and one on their right. Since forks are shared resources between neighbors, proper synchronization is required to prevent:

- Deadlocks
- Data races
- Starvation
- Undefined behavior

This project focuses on:

- Multithreading using `pthread`
- Mutex synchronization
- Race condition prevention
- Precise timing control
- Safe thread termination
- Concurrent state monitoring

The simulation ends when:
- A philosopher dies (if they do not eat within `time_to_die`)
- OR all philosophers have eaten a specified number of times (if provided)

---

## Technical Choices

- POSIX Threads (`pthread`)
- Mutex-based synchronization
- Central monitor thread for lifecycle management
- Per-philosopher state protection using individual mutexes
- Controlled start barrier to synchronize all threads

---
## Instructions

### Build
```sh
make
```

### Run
```sh
./philo no_of_philosophers  time_to_die time_to_eat time_to_sleep   [nbr_of_times_each_philosopher_needs_to_eat]
```
### Clean
```sh
make clean
make fclean
```

### Help
```sh
make help
```
---

## Resources

### References

- ["POSIX Threads Documentation"](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- ["Mutex Documentation"](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3.html)
- ["Thread Management Functions in C"](https://www.geeksforgeeks.org/c/thread-functions-in-c-c/)
- ["The dining philoshophers (an introduction to multitasking) a 
42 The Network
 project"](https://m4nnb3ll.medium.com/the-dining-philoshophers-an-introduction-to-multitasking-a-42-the-network-project-34e4141dbc49)
- [“Deadlock Prevention Strategies”](https://www.geeksforgeeks.org/operating-systems/deadlock-prevention/)
- [“Race Conditions in C”](https://www.geeksforgeeks.org/operating-systems/race-condition-in-operating-systems/)
["Philosopher Visualizer"](https://rom98759.github.io/Philosophers-visualizer/)
- ["Enumeration (or enum) in C"](https://www.geeksforgeeks.org/c/enumeration-enum-c/)
- ["Thread synchronization"](https://jorisvr.nl/article/cpp-thread-sync)

---

## Use of AI
- AI was used for testing ideas
- For understanding tedious stuff by generating examples
- Tracing complicated errors its source.
- Help in writing the README.md
