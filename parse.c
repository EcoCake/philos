/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:32:27 by amezoe            #+#    #+#             */
/*   Updated: 2025/09/22 03:26:45 by amezoe           ###   ########.fr       */
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

void	parse_main_args(char **av, t_data *data)
{
	data->num_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
}

int	validate_main_args(t_data *data)
{
	if (data->num_philos <= 0 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
	{
		printf("ERROR, all args must be positive ints.\n");
		return (1);
	}
	return (0);
}

int	handle_optional_arg(int ac, char **av, t_data *data)
{
	if (ac == 6)
	{
		data->meals_to_eat = ft_atol(av[5]);
		if (data->meals_to_eat <= 0)
		{
			printf("ERROR, number of meals must be a positive int.\n");
			return (1);
		}
	}
	else
		data->meals_to_eat = -1;
	return (0);
}

int	parse_validation(int ac, char **av, t_data *data)
{
	if (ac < 5 || ac > 6)
	{
		printf("Invalid number of arguments.\n");
		printf("Usage: ./philo num_philos t_die t_eat t_sleep [meals]\n");
		return (1);
	}
	parse_main_args(av, data);
	if (validate_main_args(data) != 0)
		return (1);
	if (handle_optional_arg(ac, av, data) != 0)
		return (1);
	return (0);
}
