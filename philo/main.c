/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicia <alicia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:38:02 by amezoe            #+#    #+#             */
/*   Updated: 2025/09/18 20:21:28 by alicia           ###   ########.fr       */
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
		data->philos[i].last_meal_time = data->start_time;
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	monitor_sim(t_data *data)
{
	int		i;
	long	time_since_meal;
	int		is_dead;
	long	timestamp;

	while (!sim_end(data))
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->philos[i].data_lock);
			time_since_meal = get_time() - data->philos[i].last_meal_time;
			is_dead = time_since_meal > data->time_to_die;
			pthread_mutex_unlock(&data->philos[i].data_lock);
			if (is_dead)
			{
				pthread_mutex_lock(&data->sim_lock);
				if (data->dead_flag == 0)
				{
					data->dead_flag = 1;
					pthread_mutex_lock(&data->print_lock);
					timestamp = get_time() - data->start_time;
					printf("%ld %d died\n", timestamp, data->philos[i].id);
					pthread_mutex_unlock(&data->print_lock);
				}
				pthread_mutex_unlock(&data->sim_lock);
				return;
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