/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:42:56 by fda-estr          #+#    #+#             */
/*   Updated: 2023/12/03 21:49:09 by fda-estr         ###   ########.fr       */
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
	printf("Number of philos: %d\n", data->nbr_of_philo);
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

int		parsing(t_data *data, int ac, char **av)
{
	printf("Nbr of philos: %d\n", data->nbr_of_philo);

	data->nbr_of_philo = ft_atoi(av[1]);
	if (data->nbr_of_philo < 1)
		return (1);
	data->t_die = (uint64_t) ft_atoi(av[2]);
	data->t_eat = (uint64_t) ft_atoi(av[3]);
	data->t_sleep = (uint64_t) ft_atoi(av[4]);
	if (ac == 6)
		data->eat_count = ft_atoi(av[5]);
	printf("Nbr of philosophers: %d\n", data->nbr_of_philo);
	printf("Time to die: %ld\n", data->t_die);
	printf("Time to eat: %ld\n", data->t_eat);
	printf("Time to sleep: %ld\n", data->t_sleep);
	printf("Eat count: %d\n", data->eat_count);
	if (data->nbr_of_philo > 1)
		fork_maker(data);
	return (0);
}
