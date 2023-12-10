/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 22:59:32 by fda-estr          #+#    #+#             */
/*   Updated: 2023/12/10 17:22:32 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_fork2(t_data *data, t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->fork2);
		if (data->fork_status[philo->fork_status2] == 0)
		{
			data->fork_status[philo->fork_status2] = 1;
			pthread_mutex_unlock(philo->fork2);
			break ;
		}
		pthread_mutex_unlock(philo->fork2);
		if (check_pulse(data, philo) == 1)
			break ;
	}
	if (check_pulse(data, philo) == 0)
		printer(data, philo, FORK);
}

int	get_fork(t_data *data, t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->fork1);
		if (data->fork_status[philo->fork_status1] == 0)
		{
			data->fork_status[philo->fork_status1] = 1;
			pthread_mutex_unlock(philo->fork1);
			break ;
		}
		pthread_mutex_unlock(philo->fork1);
		if (check_pulse(data, philo) == 1)
			break ;
	}
	if (check_pulse(data, philo) == 0)
		printer(data, philo, FORK);
	get_fork2(data, philo);
	return (0);
}

int		to_eat(t_data *data, t_philo *philo)
{
	uint64_t	end;

	if (check_pulse(data, philo) == 0)
			philo->last_ts = printer(data, philo, EAT);
	else
		return (1);
	philo->time_of_death = philo->last_ts + philo->t_die;
	philo->eat_count++;
	end = philo->last_ts + philo->t_eat;
	if (philo->flag == 1)
		return (1);
	if (philo->eat_count == philo->max_eat)
	{
		pthread_mutex_lock(&data->eat);
		data->eaters++;
		pthread_mutex_unlock(&data->eat);
	}
	while (philo->last_ts < end)
	{
		if (check_pulse(data,philo) == 1)
			return (1);
	}
	return (0);

}

int		put_down_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->fork2);
	data->fork_status[philo->fork_status2] = 0;
	pthread_mutex_unlock(philo->fork2);
	pthread_mutex_lock(philo->fork1);
	data->fork_status[philo->fork_status1]= 0;
	pthread_mutex_unlock(philo->fork1);
	return (0);
}
int		to_sleep(t_data *data, t_philo *philo)
{
	uint64_t	end;
	
	if (check_pulse(data, philo) == 0)
			philo->last_ts = printer(data, philo, SLEEP);
	else
		return (1);
	end = philo->last_ts + philo->t_sleep;
	if (philo->flag == 1)
		return (1);
	while (philo->last_ts < end)
	{
		if (check_pulse(data, philo) == 1)
			return (1);
	}
	return (0);
}

int		to_think(t_data *data, t_philo *philo)
{
	if (check_pulse(data, philo) == 0)
			philo->last_ts = printer(data, philo, THINK);
	else
		return (1);
	return (0);
}