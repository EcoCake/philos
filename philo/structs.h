/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 03:08:05 by amezoe            #+#    #+#             */
/*   Updated: 2025/09/22 03:08:20 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

struct	s_data;

typedef enum e_philo_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_philo_state;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_meal_time;
	t_philo_state	state;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	data_lock;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				meals_to_eat;
	int				dead_flag;
	int				full_flag;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	sim_lock;
	pthread_mutex_t	print_lock;
}	t_data;

#endif