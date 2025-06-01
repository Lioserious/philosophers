/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:26:14 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/01 15:31:36 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Releases both forks after eating is complete.
 * Forks are released in the same order regardless of acquisition order.
 */
static void	release_forks(t_philosophers *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_unlock(&data->forks[philo->le_fork_index]);
	pthread_mutex_unlock(&data->forks[philo->re_fork_index]);
}

/**
 * Handles the sleeping phase of a philosopher's life cycle.
 * Prints sleeping status and sleeps for the designated sleeping time.
 */
static void	sleep_phase(t_philosophers *philo)
{
	print_status(philo, "is sleeping");
	precise_usleep(philo->data->time_to_sleep * 1000);
}

void	precise_usleep(long microseconds)
{
	long	start_time;
	long	current_time;

	start_time = get_current_time() * 1000;
	if (microseconds > 1000)
	{
		usleep(microseconds - 500);
		microseconds = 500;
	}
	current_time = get_current_time() * 1000;
	while (current_time - start_time < microseconds)
	{
		usleep(10);
		current_time = get_current_time() * 1000;
	}
}

/**
 * Main routine executed by each philosopher thread.
 * Manages the complete lifecycle: thinking -> eating -> sleeping.
* Handles special case for single philosopher and implements deadlock
 prevention.
 */
void	*philosopher_routine(void *arg)
{
	t_philosophers	*philo;
	t_data			*data;

	philo = (t_philosophers *)arg;
	data = philo->data;
	if (data->nbr_philosophers == 1)
		return (handle_single_philosopher(philo), NULL);
	if (philo->id % 2 == 0)
		usleep((data->time_to_eat * 1000) / 2);
	while (!should_stop_simulation(data))
	{
		think_phase(philo);
		acquire_forks(philo);
		if (should_stop_simulation(data))
			return (release_forks(philo), NULL);
		eat_phase(philo);
		release_forks(philo);
		sleep_phase(philo);
	}
	return (NULL);
}
