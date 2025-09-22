/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 03:06:39 by amezoe            #+#    #+#             */
/*   Updated: 2025/09/22 03:07:01 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "structs.h"

//parsing

long	ft_atol(const char *str);
void	parse_main_args(char **av, t_data *data);
int		validate_main_args(t_data *data);
int		handle_optional_arg(int ac, char **av, t_data *data);
int		parse_validation(int ac, char **av, t_data *data);

//init.c alloc philos and forks, init values and mutexes

void	init_philos(t_data *data);
int		init_sim(t_data *data);
int		sim_end(t_data *data);

// utils.c

long	get_time(void);
void	print_status(t_philo *philo, char *status);
void	cleanup(t_data *data);
void	check_if_full(t_data *data);
void	smart_sleep(long duration, t_data *data);

//routine

void	assign_forks(t_philo *philo, pthread_mutex_t **f1,
			pthread_mutex_t **f2);
void	perform_meal(t_philo *philo, pthread_mutex_t *f1,
			pthread_mutex_t *f2);
void	lock_f2_and_eat(t_philo *philo, pthread_mutex_t *f1,
			pthread_mutex_t *f2);
void	philo_eating(t_philo *philo);
void	*philo_routine(void *arg);

//main.c

int		start_sim(t_data *data);
int		is_philo_dead(t_philo *philo);
void	announce_death(t_philo *philo);
void	monitor_sim(t_data *data);
int		main(int ac, char **av);

#endif