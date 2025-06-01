/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:03:06 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/01 13:28:32 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Creates all philosopher threads and starts their execution.
 * Returns 0 on success, 1 on failure with error cleanup.
 */
static int	create_philosopher_threads(t_philosophers *philosophers,
		t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philosophers)
	{
		if (pthread_create(&philosophers[i].thread, NULL, philosopher_routine,
				&philosophers[i]) != 0)
		{
			printf("Error creating thread for philosopher %d\n", i);
			free_philosophers(philosophers);
			free_data(data);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * Creates the monitor thread that oversees all philosophers.
 * Returns 0 on success, 1 on failure with error cleanup.
 */
static int	create_monitor_thread(pthread_t *monitor_thread,
		t_philosophers *philosophers, t_data *data)
{
	if (pthread_create(monitor_thread, NULL, monitor_routine,
			philosophers) != 0)
	{
		printf("Error creating monitor thread\n");
		free_philosophers(philosophers);
		free_data(data);
		return (1);
	}
	return (0);
}

/**
 * Waits for all philosopher threads and the monitor thread to complete.
 * Ensures proper thread synchronization before program termination.
 */
static void	wait_for_all_threads(t_philosophers *philosophers,
		pthread_t monitor_thread, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philosophers)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}

/**
 * Initializes program data and philosophers based on command line arguments.
 * Returns 0 on success, 1 on failure with proper cleanup.
 */
static int	initialize_simulation(int argc, char **argv, t_data **data,
		t_philosophers **philosophers)
{
	*data = init_data(argc, argv);
	if (!*data)
		return (1);
	*philosophers = init_philosophers(*data);
	if (!*philosophers)
	{
		free_data(*data);
		return (1);
	}
	return (0);
}

/**
 * Main entry point of the dining philosophers simulation.
 * Validates arguments, initializes simulation, creates threads,
	and manages cleanup.
 */
int	main(int argc, char *argv[])
{
	t_data			*data;
	t_philosophers	*philosophers;
	pthread_t		monitor_thread;

	data = NULL;
	philosophers = NULL;
	if (!validate_arguments(argc, argv))
		return (print_instructions(), 1);
	if (initialize_simulation(argc, argv, &data, &philosophers) != 0)
		return (1);
	if (create_philosopher_threads(philosophers, data) != 0)
		return (1);
	if (create_monitor_thread(&monitor_thread, philosophers, data) != 0)
		return (1);
	wait_for_all_threads(philosophers, monitor_thread, data);
	free_philosophers(philosophers);
	free_data(data);
	return (0);
}
