/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:55:28 by amezoe            #+#    #+#             */
/*   Updated: 2025/09/16 17:19:18 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	else
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	pthread_mutex_lock(first_fork);
	if (sim_end(philo->data))
	{
		pthread_mutex_unlock(first_fork); 
		return;
	}
	print_status(philo, "has taken a fork");
	if (philo->data->num_philos == 1)
	{
		smart_sleep(philo->data->time_to_die * 2, philo->data);
		pthread_mutex_unlock(first_fork);
		return;
	}
	pthread_mutex_lock(second_fork);
	if (sim_end(philo->data))
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return;
	}
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data_lock);
	philo->last_meal_time = get_time();
	print_status(philo, "is eating");
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data_lock);
	smart_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal_time = philo->data->start_time;
	if(philo->id % 2 == 0) //delay for even philos
		usleep(1000);
	while (!sim_end(philo->data))
	{
		philo_eating(philo);
		
		if (sim_end(philo->data))
			break ;
		
		print_status(philo, "is sleeping");
		smart_sleep(philo->data->time_to_sleep, philo->data);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
