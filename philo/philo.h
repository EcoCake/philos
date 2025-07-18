#ifndef PHILOS_H
# define PHILOS_H


# include <pthread.h>
# include <sys/time.h> // gettimeofday
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	long long		last_meal_time;
	int				eat_count;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				num_times_to_eat;
	long long		start_time;
	int				is_running; // flag to stop simulation
	pthread_mutex_t	*forks; // array of mutexes for forks
	// Add a mutex for printing to avoid interleaved messages
	pthread_mutex_t	print_mutex;
	t_philo			*philosophers; // array of philosopher structs
}	t_data;


#endif