#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h> // gettimeofday
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "structs.h"

//parsing

long	ft_atol(const char *str);
int		parse_validation(int ac, char **av, t_data *data);

//init.c alloc philos and forks, init values and mutexes

void	init_philos(t_data *data);
int		init_sim(t_data *data);
int	sim_end(t_data *data);


// utils.c

long	get_time(void);
void	print_status(t_philo *philo, char *status);
void	cleanup(t_data *data);
void	check_if_full(t_data *data);
void	smart_sleep(long duration, t_data *data);


//routine

void	philo_eating(t_philo *philo);
void	*philo_routine(void *arg);



#endif