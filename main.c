/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:38:02 by amezoe            #+#    #+#             */
/*   Updated: 2025/09/22 03:09:02 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_sim(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&philo_routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_philo_dead(t_philo *philo)
{
	long	time_since_meal;

	pthread_mutex_lock(&philo->data_lock);
	time_since_meal = get_time() - philo->last_meal_time;
	if (time_since_meal > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data_lock);
	return (0);
}

void	announce_death(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->sim_lock);
	if (philo->data->dead_flag == 0)
	{
		philo->data->dead_flag = 1;
		pthread_mutex_lock(&philo->data->print_lock);
		timestamp = get_time() - philo->data->start_time;
		printf("%ld %d died\n", timestamp, philo->id);
		pthread_mutex_unlock(&philo->data->print_lock);
	}
	pthread_mutex_unlock(&philo->data->sim_lock);
}

void	monitor_sim(t_data *data)
{
	int	i;

	while (!sim_end(data))
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (is_philo_dead(&data->philos[i]))
			{
				announce_death(&data->philos[i]);
				return ;
			}
			i++;
		}
		check_if_full(data);
		usleep(1000);
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (parse_validation(ac, av, &data) != 0)
		return (EXIT_FAILURE);
	if (init_sim(&data) != 0)
		return (EXIT_FAILURE);
	data.full_flag = 0;
	data.dead_flag = 0;
	if (start_sim(&data) != 0)
		return (cleanup(&data), EXIT_FAILURE);
	monitor_sim(&data);
	cleanup(&data);
	return (EXIT_SUCCESS);
}
