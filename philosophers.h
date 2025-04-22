/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:03:25 by lihrig            #+#    #+#             */
/*   Updated: 2025/04/22 18:18:55 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philosophers
{
	int				id;
	pthread_t		thread;
	int				le_fork_index;
	int				re_fork_index;
	long			last_meal;
	int				meals_eaten;
	struct s_data	*data;

}				t_philosophers;

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
	
	pthread_mutex_t *forks;          // Array von Gabeln (Mutexe)
    pthread_mutex_t write_mutex;     // Mutex für Ausgaben auf die Konsole
    pthread_mutex_t dead_mutex;      // Mutex für den Zugriff auf is_dead

}				t_data;

t_data *init_data(int argc, char **argv);
t_philosophers *init_philosophers(t_data *data);
long get_current_time(void);
void	print_status(t_philosophers *philo, char *status);
void	*ft_memset(void *ptr, int value, size_t nbr);

