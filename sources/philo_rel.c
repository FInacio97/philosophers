/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_rel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:32:32 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/13 01:08:29 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philos(t_philo *first)
{
	t_philo	*current;
	int		i;

	i = 150;
	current = first;
	while (current && --i)
	{
		if (!current->next_philo)
			break ;
		current = current->next_philo;
	}
}

void	fork_shifter(t_data *data)
{
	t_philo			*current;
	pthread_mutex_t	*temp;
	int				tmp;

	current = data->fst_philo;
	while (current)
	{
		if (current->philo_nbr % 2 == 0)
		{
			tmp = current->fork_status1;
			temp = current->fork1;
			current->fork_status1 = current->fork_status2;
			current->fork1 = current->fork2;
			current->fork_status2 = tmp;
			current->fork2 = temp;
		}
		current = current->next_philo;
	}
}

void	fork_placer(t_data *data)
{
	t_philo	*current;

	current = data->fst_philo;
	while (current->next_philo)
	{
		current->fork1 = &data->fork[current->philo_nbr - 1];
		current->fork_status1 = current->philo_nbr - 1;
		current->fork2 = &data->fork[current->philo_nbr];
		current->fork_status2 = current->philo_nbr;
		current = current->next_philo;
	}
	current->fork1 = &data->fork[current->philo_nbr - 1];
	current->fork_status1 = current->philo_nbr - 1;
	current->fork2 = &data->fork[0];
	current->fork_status2 = 0;
	fork_shifter(data);
}

void	philo_generator(t_data *data)
{
	int	i;

	i = 0;
	while (++i <= data->nbr_of_philo)
	{
		if (list_add_back(data, new_list(data, i)) == 1)
			printf("Error: creating philos...\n");
	}
	fork_placer(data);
}
