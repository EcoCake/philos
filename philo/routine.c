/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:55:28 by amezoe            #+#    #+#             */
/*   Updated: 2025/09/13 14:53:24 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	print_status(philo, "has taken the fork");
	print_status(philo, "has taken the fork");
	
	pthread_mutex_lock(&philo->data_lock);
	philo->last_meal_time = get_time();
	philo->eat_count++;
	print_status(philo, "is eating");
	pthread_mutex_unlock(&philo->data_lock);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
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
		print_status(philo, "is eeping");
		usleep(philo->data->time_to_sleep * 1000);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
