/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:03:25 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/24 15:39:38 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_philosophers
{
	int				id;
	pthread_t		thread;
	int				le_fork_index;
	int				re_fork_index;
	long			last_meal;
	int				meals_eaten;
	struct s_data	*data;

}					t_philosophers;

typedef struct s_data
{
	int				nbr_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				forced_to_eat;
	long			start_time;
	int				is_dead;

	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	dead_mutex;
}					t_data;

int					count_satisfied_philosophers(t_philosophers *philosophers,
						t_data *data);
// Routine helper Functions
void				handle_single_philosopher(t_philosophers *philo);
int					should_stop_simulation(t_data *data);
void				think_phase(t_philosophers *philo);
void				acquire_forks(t_philosophers *philo);
void				eat_phase(t_philosophers *philo);
// Utils for main
void				print_instructions(void);
void				free_data(t_data *data);
void				free_philosophers(t_philosophers *philosophers);

t_data				*init_data(int argc, char **argv);
t_philosophers		*init_philosophers(t_data *data);
long				get_current_time(void);
void				print_status(t_philosophers *philo, char *status);
void				*ft_memset(void *ptr, int value, size_t nbr);
void				*philosopher_routine(void *arg);
void				*monitor_routine(void *arg);
