/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:42:53 by fda-estr          #+#    #+#             */
/*   Updated: 2023/12/25 20:37:17 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av) 
{
	t_data data;

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
	else
	{
		philo_generator(&data);
		philo_birth_giver(&data);
		eat_check(&data);
		philo_retire(&data);
		fork_destroyer(&data);
		delete_list(&data);
		free (data.fork_status);
	}
}


/*
	


*/