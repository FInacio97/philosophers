/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:42:56 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/08 00:51:02 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_maker(t_data *data)
{
	int	i;

	i = -1;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philo + 1);
	if (!data->fork)
	{
		printf("Could not allocate memory: forks\n");
		return (1);
	}
	data->fork_status = malloc(sizeof(int) * data->nbr_of_philo);
	if (!data->fork_status)
	{
		printf("Could not allocate memory: forks\n");
		return (1);
	}
	while (++i < data->nbr_of_philo)
	{
		data->fork_status[i] = 0;
		if (pthread_mutex_init(&data->fork[i], NULL) == 1)
		{
			printf("Trouble creating mutex: %d\n", i);
			return (1);
		}
	}
	return (0);
}

int	parsing(t_data *data, int ac, char **av)
{
	data->nbr_of_philo = ft_atoi(av[1]);
	if (data->nbr_of_philo < 1)
		return (1);
	data->t_die = (uint64_t) ft_atoi(av[2]);
	data->t_eat = (uint64_t) ft_atoi(av[3]);
	data->t_sleep = (uint64_t) ft_atoi(av[4]);
	if (ac == 6)
		data->eat_count = ft_atoi(av[5]);
	if (data->nbr_of_philo > 1)
		fork_maker(data);
	return (0);
}
