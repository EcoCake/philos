/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:32:27 by amezoe            #+#    #+#             */
/*   Updated: 2025/09/13 14:47:43 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

long	ft_atol(const char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > (LONG_MAX - (str[i] - '0')) / 10)
			return (-1);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (res);
}

int	parse_validation(int ac, char **av, t_data *data)
{
	if(ac < 5 || ac > 6)
	{
		printf("Invalid number of args\n");
		printf("Usage: ./philo num_philos t_die t_eat t_sleep [meals]\n");
		return (1);
	}
	data->num_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (data->num_philos <= 0 || data->time_to_die < 0 || data->time_to_eat < 0 || data->time_to_sleep < 0)
	{
		printf("ERROR, all args must be positive\n");
		return (1);
	}
	if (ac == 6)
	{
		data->meals_to_eat = ft_atol(av[5]);
		if (data->meals_to_eat <= 0)
		{
			printf("ERROR, meals must be a positive int\n");
			return(1);
		}
	}
	else
		data->meals_to_eat = -1; //arg not set
	return (0);
}

