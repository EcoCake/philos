/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:55:28 by amezoe            #+#    #+#             */
/*   Updated: 2025/09/22 03:10:28 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_forks(t_philo *philo, pthread_mutex_t **f1,
		pthread_mutex_t **f2)
{
	if (philo->id % 2 == 0)
	{
		*f1 = philo->right_fork;
		*f2 = philo->left_fork;
	}
	else
	{
		*f1 = philo->left_fork;
		*f2 = philo->right_fork;
	}
}

void	perform_meal(t_philo *philo, pthread_mutex_t *f1,
		pthread_mutex_t *f2)
{
	pthread_mutex_lock(&philo->data_lock);
	philo->last_meal_time = get_time();
	print_status(philo, "is eating");
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data_lock);
	smart_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(f1);
	pthread_mutex_unlock(f2);
}

void	lock_f2_and_eat(t_philo *philo, pthread_mutex_t *f1,
		pthread_mutex_t *f2)
{
	pthread_mutex_lock(f2);
	if (sim_end(philo->data))
	{
		pthread_mutex_unlock(f1);
		pthread_mutex_unlock(f2);
		return ;
	}
	print_status(philo, "has taken a fork");
	perform_meal(philo, f1, f2);
}

void	philo_eating(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	assign_forks(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	if (sim_end(philo->data))
	{
		pthread_mutex_unlock(first_fork);
		return ;
	}
	print_status(philo, "has taken a fork");
	if (philo->data->num_philos == 1)
	{
		smart_sleep(philo->data->time_to_die * 2, philo->data);
		pthread_mutex_unlock(first_fork);
		return ;
	}
	lock_f2_and_eat(philo, first_fork, second_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
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
