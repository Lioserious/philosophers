/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:03:22 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/01 14:09:45 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Calculates the optimal thinking time based on eating and sleeping times.
* Returns a thinking time that prevents philosophers from competing too
 aggressively.
 */
static int	calculate_think_time(int time_to_eat, int time_to_sleep)
{
	int	think_time;

	if (time_to_eat >= time_to_sleep)
		think_time = 1;
	else
		think_time = (time_to_sleep - time_to_eat) / 2;
	if (think_time < 1)
		think_time = 1;
	return (think_time);
}

/**
 * Initializes timing parameters from command line arguments.
 * Sets up all time-related data including the calculated thinking time.
 */
static void	init_timing_data(t_data *data, int argc, char **argv)
{
	data->nbr_philosophers = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->time_to_think = calculate_think_time(data->time_to_eat,
			data->time_to_sleep);
	if (argc == 6)
		data->forced_to_eat = atoi(argv[5]);
	else
		data->forced_to_eat = 0;
}

/**
 * Initializes all fork mutexes for the philosophers.
 * Returns 0 on success, 1 on failure.
 */
static int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philosophers);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->nbr_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 * Initializes control mutexes (write_mutex and dead_mutex).
 * Returns 0 on success, 1 on failure.
 */
static int	init_control_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
		return (1);
	return (0);
}

/**
 * Main initialization function for simulation data.
 * Allocates memory and initializes all components of the data structure.
 */
t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	init_timing_data(data, argc, argv);
	data->is_dead = 0;
	data->start_time = get_current_time();
	if (init_forks(data) != 0)
	{
		free(data);
		return (NULL);
	}
	if (init_control_mutexes(data) != 0)
	{
		free_data(data);
		return (NULL);
	}
	return (data);
}
