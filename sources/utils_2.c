/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:20:50 by fda-estr          #+#    #+#             */
/*   Updated: 2023/12/03 23:40:12 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	chech_status(t_data *data, t_philo *philo)
{
	(void) philo;
	// printf("lock trylock: %d\n", philo->philo_nbr);
	pthread_mutex_lock(&data->lock);
	// printf("lock lock: %d\n", philo->philo_nbr);
	if (data->flag_of_death == 1)
	{
		pthread_mutex_unlock(&data->lock);
		// printf("lock unlock: %d\n", philo->philo_nbr);
		return (1);
	}
	pthread_mutex_unlock(&data->lock);
	// printf("lock unlock: %d\n", philo->philo_nbr);
	return (0);
}

int	check_pulse(t_data *data, t_philo *philo)
{
	philo->last_ts = time_stamp_philo(philo);
	if (philo->last_ts > philo->time_of_death)
	{
		// printf("lock trylock: %d\n", philo->philo_nbr);
		pthread_mutex_lock(&data->lock);
		// printf("lock lock: %d\n", philo->philo_nbr);
		// if (data->flag_of_death == 1)
		// 	return (1);
		data->flag_of_death = 1;
		printer(data, philo, DIE);
		pthread_mutex_unlock(&data->lock);
		// printf("lock unlock: %d\n", philo->philo_nbr);
		return (1);
	}
	return (0);
}

uint64_t	printer(t_data *data, t_philo *philo, char *state)
{
	uint64_t	ts;

	// printf("printer trylock: %d\n", philo->philo_nbr);
	pthread_mutex_lock(&data->printer);
	// printf("printer lock: %d\n", philo->philo_nbr);
	ts = time_stamp_philo(philo);
	printf("%ldms %d %s\n", ts, philo->philo_nbr, state);
	pthread_mutex_unlock(&data->printer);
	// printf("printer unlock: %d\n", philo->philo_nbr);
	return (ts);
}
