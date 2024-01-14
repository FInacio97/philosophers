/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:20:50 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/13 01:06:59 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	chech_status(t_data *data, t_philo *philo)
{
	(void) philo;
	if (data->flag_of_death == 1)
		return (1);
	return (0);
}

int	check_pulse(t_data *data, t_philo *philo)
{
	philo->last_ts = time_stamp_philo(philo);
	if (philo->last_ts > philo->time_of_death)
	{
		pthread_mutex_lock(&data->lock);
		if (data->flag_of_death == 0)
		{
			data->flag_of_death = 1;
			pthread_mutex_lock(&data->printer);
			printf("%ld %d %s\n", philo->last_ts, philo->philo_nbr, DIE);
			pthread_mutex_unlock(&data->printer);
			philo->flag = 1;
		}
		pthread_mutex_unlock(&data->lock);
		return (1);
	}
	return (0);
}

uint64_t	printer(t_data *data, t_philo *philo, char *state)
{
	uint64_t	ts;

	pthread_mutex_lock(&data->lock);
	pthread_mutex_lock(&data->printer);
	if (chech_status(data, philo) == 1)
	{
		philo->flag = 1;
		pthread_mutex_unlock(&data->printer);
		pthread_mutex_unlock(&data->lock);
		return (0);
	}
	ts = time_stamp_philo(philo);
	printf("%ld %d %s\n", ts, philo->philo_nbr, state);
	pthread_mutex_unlock(&data->printer);
	pthread_mutex_unlock(&data->lock);
	return (ts);
}

void	one_philo(t_data *data)
{
	printf (CYAN"0\t" GREEN"1\t" YELLOW"has taken a fork\n" RESET);
	usleep(data->t_die * 1000);
	printf (CYAN"%lu\t" GREEN"1\t" RED"died\n" RESET, data->t_die);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != 0)
	{
		res *= 10;
		res += str[i] - 48;
		i++;
	}
	return (res * sign);
}
