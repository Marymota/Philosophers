# Philosophers

Philosopher with threads and mutex

<img width="500" alt="working for the most part" src="https://github.com/Marymota/Images-/blob/master/robots.png">

---

# Briefing

- One or more philosophers are sitting at a round table either eating, either thinking, either sleeping. While they are eating, they do not think or sleep; while thinking they don’t eat or sleep; and, of course, while sleeping, they do not eat or think.
- The philosophers sit at a circular table with a large bowl of spaghetti in the center.
- There are some forks on the table. Serving and eating spaghetti with a single fork is very inconvenient, so the philosophers will eat with two forks, one for each hand.
- Each time a philosopher finishes eating, they will drop their forks and start sleeping.
- Once they have finished sleeping, they will start thinking. The simulation stops when a philosopher dies.
- Every philosopher needs to eat and they should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know when another philosopher is about to die.
- No need to say that philosophers should avoid dying!

---

**Program name: ***philo*

- **Arguments:**
    - ***number_of_philosophers :** is the number of philosophers and also the number of forks.*
    - ***time_to_die :** is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting their last meal or the beginning of the simulation, it dies.*
    - ***time_to_eat :** is in milliseconds and is the time it takes for a philosopher to eat. During that time they will need to keep the two forks.*
    - ***time_to_sleep :** is in milliseconds and is the time the philosopher will spend sleeping.*
    - ***[number_of times_each_philosopher_must_eat] :** argument is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.*
    
- **External functs.**
    - **<string.h>**
        - memset
    - **<stdio.h>**
        - printf
    - **<stdlib.c>**
        - free
        - malloc
    - **<unistd.h>**
        - write
        - usleep
    - **<sys/time.h>**
        - gettimeofday
    - **<pthread.h>**
        - pthread_create - create a new thread
        - pthread_detach - put a running thread in the detached state
        - pthread_join - wait for termination of another thread
        - pthread_mutex_init - operations on mutexes
        - pthread_mutex_destroy [pthread_mutex_init] - operations on mutexes
        - pthread_mutex_lock [pthread_mutex_init] - operations on mutexes
        - pthread_mutex_unlock [pthread_mutex_init] - operations on mutexes
- **Philosophers identity and positions**
    - Each philosopher should be given a number from 1 to ’number_of_philosophers’. Philosopher number 1 is next to philosopher number ’number_of_philosophers’. Any other philosopher with the number N is seated between philosopher N - 1 and philosopher N + 1
- **Philosophers states**
    
    Any change of status of a philosopher must be written as follows (with X replaced with the philosopher number and timestamp_in_ms the current timestamp in milliseconds):
    
    - timestamp_in_ms X has taken a fork
    - timestamp_in_ms X is eating
    - timestamp_in_ms X is sleeping
    - timestamp_in_ms X is thinking
    - timestamp_in_ms X died
    
    The status printed should not be scrambled or intertwined with another philosopher’s status.
    
    You can’t have more than 10 ms between the death of a philosopher and when it will print its death.
    
    Philosophers should avoid dying!
    

---

## Technical Info

- Each philosopher should be a thread
    
    <aside>
    📖 Thread
    
    - What are [**threads**](https://www.computerworld.com/article/2585661/processes-and-threads.html) ?
        
        *A thread has its own flow of control, but it shares the same address space and most data with all other threads running in the same process. 
        It takes much less CPU time to switch among threads than between processes, because there's no need to switch address spaces and also threads in a process can communicate more easily with one another.* 
        
    - How to [create a **thread](https://www.tutorialspoint.com/multithreading-in-c)** ?
        
        ```c
        #include <pthread.h>
        
        pthreads_t philosophers[NUM_PHILOS];
        pthread_create (philosophers[i], NULL, start_routine, (void *)i);
        ```
        
    </aside>
    
- One fork between each philosopher, therefore if they are multiple philosophers, there will be a fork at the right and the left of each philosopher.
    
    <aside>
    🛸 What does ***forks*** mean in the context of a program ?
    
    </aside>
    
- To avoid philosophers duplicating forks, you should protect the forks state with a *mutex* for each of them.
    
    <aside>
    📖 Mutex
    
    - What is a **mutex**?
        
        **[Mutex** - Mutual Exclusion Object](https://www.webopedia.com/definitions/mutex/)
        
        Program object that allows multiple program threads to share the same resource, such as file access, but not simultaneously. When a program is started, a mutex is created with a unique name. After this stage, any thread that needs the resource must lock the mutex from other threads while it is using the resource. The mutex is set to unlock when the data is no longer needed or the routine is finished. 
        
    - [How to create a **mutex**?](https://www.delftstack.com/howto/c/mutex-in-c/)
        
        ```c
        pthread_mutex_t mutex = PTHERAD_MUTEX_INITIALIZER;
        
        pthread_mutex_lock(&mutex);
        pthread_mutex_unlock(&mutex);
        ```
        
    </aside>
    

---

### Glossary

- Process flow
    
    *A process is a place to work (address space) and a way to keep track of what a program is doing (flow of control). When several programs are running at the same time, each has its own address space and flow of control.*
    

- Context switching
    
    *The act of moving from one process to another. It means reprogramming the MMU to point to a different address space and restoring process information.*
    

- Memory Management Units (MMU)
    
    *Prevents any process from overrunning another address space.*
    

- [Parallel processing](https://www.tutorialspoint.com/what-is-parallel-processing)
    
    *Approach to create simultaneous data-processing functions to improve the computational speed of a computer system. Rather than processing each instruction sequentially, a parallel processing system can implement concurrent data processing.* 
    

- [Distributed processing](https://www.techopedia.com/definition/3351/distributed-processing)
    
    *Setup in which multiple individual central processing units (CPU) work on the same program, functions or systems to provide more capability for a computer or other device.* 
    
- [Thread-safe code](https://en.wikipedia.org/wiki/Thread_safety)
    
    Concept applicable to multi-threaded code. Thread-safe code only manipulates shared data in a manner that ensures that all threads behave properly and fulfill their design specifications without unintended interactions. 
    

- [Race condition](https://en.wikipedia.org/wiki/Race_condition#Computing)
    
    The condition of an electronics, software, or other system where the system's substantive behavior is dependent on the sequence or timing of other uncontrollable events. It becomes a bug when one or more of the possible behaviors is undesirable.
    

- Deadlock
    
    State in which each member of a group waits for another member, including itself, to take action, such as sending message or more commonly releasing a lock. 
    

### Processes vs. Threads

Processes can contain multiple threads. All processes will have different process IDs but threads on the same process will share the same ID. All threads access the same variables and share the same address space. 

### Solving Race Condition

**Race conditions** are solved by creating locks that define if a thread can access a chunk of memory or if other thread is accessing it. When a thread accesses memory it locks it until the interaction is finished. When the thread finishes its work on that chunk of memory it unlocks it so that other threads can access it. The 'locks' in this case are called **[mutex](https://www.notion.so/Philosophers-82562159912346f0b3df30ce681daf4a)**.

### Deadlock

[Necessary conditions for deadlock:](https://www.youtube.com/watch?v=CRIqDK8zdY0)

- **Bounded resources** (If there are infinite resources there is no Deadlock)
- **No preemption** (If a thread acquire a resource, its ownership can't be revoked)
- **Wait while holding** (Multiple independent requests)
- **Circular waiting** (Each thread is waiting for a resource held by another)

# BluePrint
  
  <img width="500" alt="working for the most part" src="https://github.com/Marymota/Images-/blob/master/philosophers_parsing_info_setup.png">
  <img width="500" alt="working for the most part" src="https://github.com/Marymota/Images-/blob/master/philosophers_parsing_info_setup_init.png">
  <img width="500" alt="working for the most part" src="https://github.com/Marymota/Images-/blob/master/philosophers_parsing_info_setup_simulation.png">
  <img width="500" alt="working for the most part" src="https://github.com/Marymota/Images-/blob/master/philosophers_parsing_info_setup_actions.png">

  

## Resources

Threads explanation in the context of the problem: [https://docs.oracle.com/cd/E19205-01/820-0619/gepji/index.html](https://docs.oracle.com/cd/E19205-01/820-0619/gepji/index.html)

Algorithm explained : [https://osandnetworkingcslab.wordpress.com/implementation-of-dining-philosophers-using-threads/](https://osandnetworkingcslab.wordpress.com/implementation-of-dining-philosophers-using-threads/)

PThreads tutorial - [https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)

https://github.com/f0rkr/philosophers & [https://f0rkr.github.io/dining-philosophers-problem/](https://f0rkr.github.io/dining-philosophers-problem/)

[Evaluation Criteria](https://www.notion.so/Evaluation-Criteria-170f4fec22294007bdd8bd431517b589)
