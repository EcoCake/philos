/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:47:52 by amezoe            #+#    #+#             */
/*   Updated: 2025/09/16 17:19:40 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *status)
{

	long	timestamp;
	int		is_dead;

	pthread_mutex_lock(&philo->data->print_lock);
	is_dead = philo->data->dead_flag;
	if (!is_dead)
	{
		timestamp = get_time() - philo->data->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].data_lock);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->sim_lock);
	free(data->philos);
	free (data->forks);
}

void	check_if_full(t_data *data)
{
	int	i;
	int	full_philo_count;

	if(data->meals_to_eat == -1)
		return ;
	i = 0;
	full_philo_count = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].data_lock);
		if (data->philos[i].eat_count >= data->meals_to_eat)
			full_philo_count++;
		pthread_mutex_unlock(&data->philos[i].data_lock);
		i++;
	}
	if (full_philo_count == data->num_philos)
	{
		pthread_mutex_lock(&data->sim_lock);
		data->full_flag = 1;
		pthread_mutex_unlock(&data->sim_lock);
	}
}

void	smart_sleep(long duration, t_data *data)
{
	long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < duration)
	{
		if (sim_end(data))
			break;
		usleep(100);
	}
}
