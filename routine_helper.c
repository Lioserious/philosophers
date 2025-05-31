/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:27:47 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/31 17:01:48 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Handles the special case of a single philosopher who cannot eat
 * because they need two forks but only one is available.
 * The philosopher will think, take one fork, then wait to die.
 */
void	handle_single_philosopher(t_philosophers *philo)
{
	t_data	*data;

	data = philo->data;
	print_status(philo, "is thinking");
	usleep(data->time_to_think * 1000);
	print_status(philo, "has taken a fork");
	usleep(data->time_to_die * 1000 + 1000);
}

/**
 * Checks if the simulation should continue by verifying if any philosopher
 * has died. Returns 1 if simulation should stop, 0 if it should continue.
 */
int	should_stop_simulation(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->dead_mutex);
	stop = data->is_dead;
	pthread_mutex_unlock(&data->dead_mutex);
	return (stop);
}

/**
 * Handles the thinking phase of a philosopher's life cycle.
 * Prints thinking status and sleeps for the designated thinking time.
 */
void	think_phase(t_philosophers *philo)
{
	print_status(philo, "is thinking");
	if (philo->data->time_to_think > 0)
		usleep(philo->data->time_to_think * 1000);
}

/**
 * Attempts to acquire both forks needed for eating.
 * Uses different fork acquisition order based on philosopher ID
 * to prevent deadlock situations.
 */
void	acquire_forks(t_philosophers *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->le_fork_index]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&data->forks[philo->re_fork_index]);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->re_fork_index]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&data->forks[philo->le_fork_index]);
		print_status(philo, "has taken a fork");
	}
}

/**
 * Handles the eating phase of a philosopher's life cycle.
 * Updates last meal time, sleeps for eating duration,
	and increments meal count.
 */
void	eat_phase(t_philosophers *philo)
{
	t_data	*data;

	data = philo->data;
	print_status(philo, "is eating");
	pthread_mutex_lock(&data->dead_mutex);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&data->dead_mutex);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_lock(&data->dead_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->dead_mutex);
}
