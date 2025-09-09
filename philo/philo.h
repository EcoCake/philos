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


#endif