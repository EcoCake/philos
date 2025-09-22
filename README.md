# Dining Philosophers

> A classic synchronization problem solved with C, threads, and mutexes.

![Language](https://img.shields.io/badge/language-C-blue.svg)
![42 Project](https://img.shields.io/badge/project-42%20Core%20Curriculum-black.svg)

This project is a simulation of the classic Dining Philosophers problem, a metaphor for illustrating and solving synchronization issues in concurrent programming. The primary challenge is to prevent deadlocks and race conditions, ensuring that no philosopher starves due to flawed logic.

---
## The Problem

The simulation is governed by a simple set of rules:
* A number of philosophers are seated at a circular table.
* Between each pair of adjacent philosophers is a single fork.
* To eat, a philosopher must acquire two forks: the one on their left and the one on their right.
* Philosophers alternate between three states: eating, sleeping, and thinking.
* If a philosopher does not eat within a specific `time_to_die`, they starve and the simulation ends.

---
## Usage

### Compilation
Clone the repository and run `make`:
```bash
git clone [your-repo-link]
cd philosophers
make
```

### Execution
The program is run with the following arguments:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
```
| Argument                  | Description                                                                    |
| :------------------------ | :----------------------------------------------------------------------------- |
| `number_of_philosophers`  | The number of philosophers and forks at the table.                             |
| `time_to_die`             | The time in milliseconds a philosopher can go without eating before dying.     |
| `time_to_eat`             | The time in milliseconds it takes to eat.                                      |
| `time_to_sleep`           | The time in milliseconds a philosopher sleeps.                                 |
| `[number_of_meals]`       | **Optional:** The simulation stops after all philosophers have eaten this many times. |

---
## Solution Overview

This implementation successfully solves the problem using the following concepts:

* **Threads**: Each philosopher is simulated in a dedicated `pthread`. This allows for concurrent execution of their actions.

* **Mutexes**: Each fork is protected by a `pthread_mutex_t` to ensure exclusive access. This prevents two philosophers from picking up the same fork simultaneously.

* **Deadlock Prevention**: A lock hierarchy is established by having odd and even-numbered philosophers acquire forks in a different order. This strategy breaks the circular wait condition that leads to deadlocks.

* **Race Condition Prevention**: All shared data is protected by dedicated mutexes. A central **monitor thread** acts as the impartial observer of the simulation, responsible for:
    * Continuously checking each philosopher's health.
    * Ensuring that if a philosopher starves, their death is announced **precisely on time** and the simulation halts immediately.
    * Cleanly terminating the simulation when all philosophers have completed their required meals.

    This code has been verified to be race-free with `valgrind --tool=helgrind`.