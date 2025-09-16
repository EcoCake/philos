/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:38:02 by amezoe            #+#    #+#             */
/*   Updated: 2025/09/16 17:01:19 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	start_sim(t_data *data)
{
	int i;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].data_lock);
		data->philos[i].last_meal_time = data->start_time;
		pthread_mutex_unlock(&data->philos[i].data_lock);
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	monitor_sim(t_data *data)
{
	int	i;
	long	timestamp;

	while (!sim_end(data))
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->philos[i].data_lock);
			if (get_time() - data->philos[i].last_meal_time > data->time_to_die)
			{
				pthread_mutex_lock(&data->print_lock);
				if (data->dead_flag == 0)
				{
					data->dead_flag = 1;
					timestamp = get_time() - data->start_time;
					printf("%ld %d died\n", timestamp, data->philos[i].id);
				}
				pthread_mutex_unlock(&data->print_lock);
				pthread_mutex_unlock(&data->philos[i].data_lock);
				return;
			}
			pthread_mutex_unlock(&data->philos[i].data_lock);
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