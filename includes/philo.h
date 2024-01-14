/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:43:01 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/13 01:09:28 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>
# include <unistd.h>
# include <limits.h>
# include <time.h>

# define GREEN	"\033[0;32m"
# define RED	"\033[0;31m"
# define YELLOW	"\x1b[33m"
# define CYAN	"\x1b[36m"
# define RESET	"\033[0m"

# define FORK	"\x1b[33mhas taken a fork\033[0m"
# define EAT	"\x1b[35mis eating\033[0m"
# define SLEEP	"\x1b[34mis sleeping\033[0m"
# define THINK	"\033[38;5;203mis thinking\033[0m"
# define DIE	"\033[0;31mdied\033[0m"

typedef struct s_philo
{
	pthread_t		thread;
	int				philo_nbr;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	int				fork_status1;
	int				fork_status2;
	struct s_philo	*next_philo;
	struct s_data	*philo_data;
	uint64_t		t_die;
	uint64_t		t_eat;
	uint64_t		t_sleep;
	uint64_t		start_time;
	uint64_t		time_of_death;
	uint64_t		time_unthink;
	uint64_t		last_ts;
	int				max_eat;
	int				eat_count;
	int				flag;
}				t_philo;

typedef struct s_data
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	lock;
	pthread_mutex_t	eat;
	pthread_mutex_t	printer;
	int				*fork_status;
	int				nbr_of_philo;
	uint64_t		t_die;
	uint64_t		t_eat;
	uint64_t		t_sleep;
	int				eat_count;
	int				flag_of_death;
	uint64_t		start_time;
	t_philo			*fst_philo;
	int				eaters;
}				t_data;

/*PARSING*/
int			fork_maker(t_data *data);
int			parsing(t_data *data, int ac, char **av);
int			fork_maker(t_data *data);
void		fork_placer(t_data *data);

/*ACTIONS*/
int			get_fork(t_data *data, t_philo *philo);
int			to_eat(t_data *data, t_philo *philo);
int			put_down_fork(t_data *data, t_philo *philo);
int			to_sleep(t_data *data, t_philo *philo);
int			to_think(t_data *data, t_philo *philo);

/*PHILO_CYCLES*/
void		*philo_cycle(void *phil);
void		philo_birth_giver(t_data *data, t_philo *nd);
void		philo_retire(t_data *data);
void		info_philo(t_data *data);
void		eat_check(t_data *data, uint64_t check_time, uint64_t ts);

/*UTILS*/
void		initializer(t_data *data);
void		fork_destroyer(t_data *data);
void		beggining_time_stamp(t_data *data);
uint64_t	time_stamp(t_data *data);
uint64_t	time_stamp_philo(t_philo *philo);

/*PHILO RELATIVES*/
void		print_philos(t_philo *first);
void		fork_shifter(t_data *data);
void		philo_generator(t_data *data);

/* UTILS 2*/
int			chech_status(t_data *data, t_philo *philo);
int			check_pulse(t_data *data, t_philo *philo);
uint64_t	printer(t_data *data, t_philo *philo, char *state);
void		one_philo(t_data *data);
int			ft_atoi(char *s);

/* LISTS */
void		delete_list(t_data *data);
t_philo		*new_list(t_data *data, int philo_nbr);
int			list_add_back(t_data *data, t_philo *node);

#endif