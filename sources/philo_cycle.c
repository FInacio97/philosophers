/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 22:45:03 by fda-estr          #+#    #+#             */
/*   Updated: 2023/12/03 23:30:10 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_cycle(void *phil)
{
	t_data *data;
	t_philo *philo;

	philo = (t_philo *) phil;
	data = philo->philo_data;
	while (1)
	{
		if (get_fork(data, philo) == 1)
			break ;
		if (to_eat(data, philo) == 1)
		{
			put_down_fork(data, philo);
			break ;
		}

		put_down_fork(data, philo);
		if (to_sleep(data, philo) == 1)
			break;
		if (to_think(data, philo) == 1)
			break ;
	}
	return (NULL);
}

void	info_philo(t_data *data)
{
	t_philo *current;

	current = data->fst_philo;
	while (current)
	{
		current->start_time = data->start_time;
		current = current->next_philo;
	}
}

void	philo_birth_giver(t_data *data)
{
	t_philo	*current;

	current = data->fst_philo;
	beggining_time_stamp(data);
	info_philo(data);
	while (current)
	{
		if (current->philo_nbr % 2 == 0)
		{
			current->philo_data = data;
			if (pthread_create(&current->thread, NULL, philo_cycle, (void *)current) != 0)
				printf("Error: fail to create thread nbr %d\n", current->philo_nbr);
		}
		current = current->next_philo;
	}
	current = data->fst_philo;
	while (current)
	{
		if (current->philo_nbr % 2 != 0)
		{
			current->philo_data = data;
			if (pthread_create(&current->thread, NULL, philo_cycle, (void *)current) != 0)
				printf("Error: fail to create thread nbr %d\n", current->philo_nbr);
		}
		current = current->next_philo;
	}
}

void	philo_retire(t_data *data)
{
	t_philo	*current;
	int		i;

	current = data->fst_philo;
	i = 0;
	while (++i <= data->nbr_of_philo)
	{
		pthread_join(current->thread, NULL);
		// printf("philo %d retired...\n", current->philo_nbr);
		current = current->next_philo;
	}
}

