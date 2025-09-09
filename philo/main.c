/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:38:02 by amezoe            #+#    #+#             */
/*   Updated: 2025/09/09 14:15:51 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int main(int ac, char **av)
{
	t_data	data;

	if (parse_validation(ac, av, &data) != 0)
		return (EXIT_FAILURE);
	if (init_sim(&data) != 0)
		return (EXIT_FAILURE);
	printf("yay! works.\n");
	return (EXIT_SUCCESS);
}