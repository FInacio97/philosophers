/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_rel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:32:32 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/07 14:42:28 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	delete_list(t_data *data)
{
	t_philo *temp;
	int		i;

	i = 0;
	while (++i <= data->nbr_of_philo)
	{
		temp = data->fst_philo->next_philo;
		free (data->fst_philo);
		data->fst_philo = temp;
	}
}

t_philo	*new_list(t_data *data, int philo_nbr)
{
	t_philo *node;

	node = (t_philo *)malloc(sizeof(t_philo));
	if (!node)
		return (NULL);
	node->philo_nbr = philo_nbr;
	node->fork1 = NULL;
	node->fork2 = NULL;
	node->fork_status1 = 0;
	node->fork_status2 = 0;
	node->flag = 0;
	node->next_philo = NULL;
	node->philo_data = NULL;
	node->t_die = data->t_die;
	node->t_eat = data->t_eat;
	node->t_sleep = data->t_sleep;
	node->start_time = 0;
	node->time_of_death = data->t_die;
	node->last_ts = 0;
	node->max_eat = 0;
	node->eat_count = 0;
	node->time_unthink = 0;
	return (node);
}

int	list_add_back(t_data *data, t_philo *node)
{
	t_philo *current;

	current = data->fst_philo;
	if (!node)
		return (1);
	node->max_eat = data->eat_count;
	if (!data->fst_philo)
	{
		data->fst_philo = node;
		return (0);
	}
	while (current->next_philo)
		current = current->next_philo;
	current->next_philo = node;
	return (0);
	
}

void	print_philos(t_philo *first)
{
	t_philo *current;
	int i;

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
	t_philo 		*current;
	pthread_mutex_t *temp;
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
	t_philo *current;

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