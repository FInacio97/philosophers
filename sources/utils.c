/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:42:58 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/13 01:09:48 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initializer(t_data *data)
{
	data->eat_count = -1;
	data->nbr_of_philo = 0;
	data->t_die = 0;
	data->t_eat = 0;
	data->t_sleep = 0;
	data->fst_philo = NULL;
	data->start_time = 0;
	data->flag_of_death = 0;
	data->fork = NULL;
	data->fork_status = NULL;
	data->eaters = 0;
	if (pthread_mutex_init(&data->lock, NULL) == 1)
	{
		printf("Trouble creating mutex\n");
	}
	if (pthread_mutex_init(&data->eat, NULL) == 1)
	{
		printf("Trouble creating mutex\n");
	}
	if (pthread_mutex_init(&data->printer, NULL) == 1)
	{
		printf("Trouble creating mutex\n");
	}
}

void	fork_destroyer(t_data *data)
{
	int	i;

	i = 0;
	while (++i < data->nbr_of_philo)
		pthread_mutex_destroy(&data->fork[i]);
	free (data->fork);
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->eat);
	pthread_mutex_destroy(&data->printer);
}

void	beggining_time_stamp(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		printf("Error: time stamp\n");
	data->start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

uint64_t	time_stamp(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		printf("Error: time stamp\n");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - data->start_time);
}

uint64_t	time_stamp_philo(t_philo *philo)
{
	struct timeval	time;
	uint64_t		res;

	if (gettimeofday(&time, NULL) < 0)
		printf("Error: time stamp\n");
	res = (time.tv_sec * 1000) + (time.tv_usec / 1000) - philo->start_time;
	return (res);
}
