/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:42:53 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/08 00:52:35 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
	{
		printf("Wrong number of arguments...");
		return (1);
	}
	initializer(&data);
	if (parsing(&data, ac, av) == 1)
	{
		printf("Invalid arguments...\n");
		return (1);
	}
	if (data.nbr_of_philo == 1)
		one_philo(&data);
	else if (data.eat_count != 0)
	{
		philo_generator(&data);
		philo_birth_giver(&data, NULL);
		eat_check(&data, 0, time_stamp(&data));
		philo_retire(&data);
		delete_list(&data);
	}
	free (data.fork_status);
	fork_destroyer(&data);
}
