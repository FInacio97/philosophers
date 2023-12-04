/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 22:59:32 by fda-estr          #+#    #+#             */
/*   Updated: 2023/12/03 23:42:30 by fda-estr         ###   ########.fr       */
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
		pthread_mutex_unlock(philo->fork1);
		if (check_pulse(data, philo) == 1)
			break ;
	}
	if (chech_status(data) == 0 && check_pulse(data, philo) == 0)
		printf("%ld %d %s\n", time_stamp_philo(philo), philo->philo_nbr, FORK);
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
			break;
	}
	if (chech_status(data) == 0 && check_pulse(data, philo) == 0)
		printf("%ld %d %s\n", time_stamp_philo(philo), philo->philo_nbr, FORK);
	get_fork2(data, philo);
	return (0);
}

int		to_eat(t_data *data, t_philo *philo)
{
	uint64_t	end;

	if (chech_status(data) == 0 && check_pulse(data, philo) == 0)
	{
		philo->last_ts = time_stamp_philo(philo);
		printf("%ld %d %s\n", philo->last_ts, philo->philo_nbr, EAT);
	}
	else
		return (1);
	// printf("philo nbr %d\n", philo->philo_nbr);
	philo->time_of_death = philo->last_ts + philo->t_die;
	end = philo->last_ts + philo->t_eat;
	philo->eat_count++;
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
	
	if (chech_status(data) == 0 && check_pulse(data, philo) == 0)
	{
		philo->last_ts = time_stamp_philo(philo);
		printf("%ld %d %s\n", philo->last_ts, philo->philo_nbr, SLEEP);
	}
	else
		return (1);
	end = philo->last_ts + philo->t_sleep;
	while (philo->last_ts < end)
	{
		if (check_pulse(data, philo) == 1)
			return (1);
	}
	return (0);
}

int		to_think(t_data *data, t_philo *philo)
{
	if (chech_status(data) == 0 && check_pulse(data, philo) == 0)
	{
		philo->last_ts = time_stamp_philo(philo);
		printf("%ld %d %s\n", philo->last_ts, philo->philo_nbr, THINK);
	}
	else
		return (1);
	return (0);
}