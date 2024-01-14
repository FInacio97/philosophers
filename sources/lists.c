/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:02:59 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/13 01:08:35 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	delete_list(t_data *data)
{
	t_philo	*temp;
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
	t_philo	*node;

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
	t_philo	*current;

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
