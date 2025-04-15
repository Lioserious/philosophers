/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:03:25 by lihrig            #+#    #+#             */
/*   Updated: 2025/04/15 17:26:06 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>

typedef struct s_philosophers
{
	int				id;
	pthread_t		thread;
	int				le_fork_index;
	int				re_fork_index;
	long			last_meal;
	struct s_data	*data;

}				t_philosophers;

typedef struct s_data
{
	int				nbr_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				forced_to_eat;
	long			start_time;
	int				is_dead;
	
	pthread_mutex_t *forks;          // Array von Gabeln (Mutexe)
    pthread_mutex_t write_mutex;     // Mutex für Ausgaben auf die Konsole
    pthread_mutex_t dead_mutex;      // Mutex für den Zugriff auf is_dead

}				t_data;
