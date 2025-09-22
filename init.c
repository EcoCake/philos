/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:36:01 by amezoe            #+#    #+#             */
/*   Updated: 2025/09/22 03:07:52 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].state = THINKING;
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].data_lock, NULL);
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		i++;
	}
}

int	init_sim(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (printf("ERROR alloc for philos\n"));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
	{
		free (data->philos);
		return (printf("ERROR alloc for forks\n"));
	}
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->sim_lock, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	data->dead_flag = 0;
	init_philos(data);
	return (0);
}

int	sim_end(t_data *data)
{
	int	ended;

	pthread_mutex_lock(&data->sim_lock);
	ended = data->dead_flag || data->full_flag;
	pthread_mutex_unlock(&data->sim_lock);
	return (ended);
}
