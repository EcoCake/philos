/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:38:02 by amezoe            #+#    #+#             */
/*   Updated: 2025/07/18 12:38:05 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int main(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf("./philo number of philos time to die time to eat time to sleep [how many times to eat]\n");
		return 1;
    }
	printf("tumber of philos: %s\n", argv[1]);
	printf("time to die: %s ms\n", argv[2]);
	printf("time to eat: %s ms\n", argv[3]);
	printf("time to sleep: %s ms\n", argv[4]);
	if (argc == 6) 
	{
		printf("Number of times each philosopher must eat: %s\n", argv[5]);
	}
	return 0;
}