/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:38:02 by amezoe            #+#    #+#             */
/*   Updated: 2025/09/11 15:19:36 by amezoe           ###   ########.fr       */
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
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine, &data->philos[i]) != 0)
		{
			printf("ERROR, cant create thread");
			return (1);
		}
		i++;
	}
	return (0);
}

void	monitor_sim(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->philos[i].data_lock);
			if( get_time() - data->philos[i].last_meal_time > data->time_to_die)
			{
				print_status(&data->philos[i], "is dead");
				pthread_mutex_lock(&data->sim_lock);
				data->dead_flag = 1;
				pthread_mutex_unlock(&data->sim_lock);
				pthread_mutex_unlock(&data->philos[i].data_lock);
				return;
			}
			pthread_mutex_unlock(&data->philos[i].data_lock);
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (parse_validation(ac, av, &data) != 0)
		return (EXIT_FAILURE);
	if (init_sim(&data) != 0)
		return (EXIT_FAILURE);
	start_sim(&data);
	return (EXIT_SUCCESS);
}