/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:27:47 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/01 15:39:11 by lihrig           ###   ########.fr       */
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
	int		think_time;
	long	time_since_meal;
	long	time_until_death;

	print_status(philo, "is thinking");
	pthread_mutex_lock(&philo->data->dead_mutex);
	time_since_meal = get_current_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->data->dead_mutex);
	time_until_death = philo->data->time_to_die - time_since_meal;
	think_time = philo->data->time_to_think;
	if (time_until_death < (philo->data->time_to_eat + 50))
		think_time = 1;
	else if (time_until_death < (philo->data->time_to_eat + 100))
		think_time = think_time / 2;
	if (think_time > 0)
		precise_usleep(think_time * 1000);
}

/**
 * Attempts to acquire both forks needed for eating.
 * Uses different fork acquisition order based on philosopher ID
 * to prevent deadlock situations.
 */
void acquire_forks(t_philosophers *philo)
{
    t_data *data = philo->data;
    int first_fork;
	int second_fork;
    
    if (philo->le_fork_index < philo->re_fork_index)
    {
        first_fork = philo->le_fork_index;
        second_fork = philo->re_fork_index;
    }
    else
    {
        first_fork = philo->re_fork_index;
        second_fork = philo->le_fork_index;
    }
    pthread_mutex_lock(&data->forks[first_fork]);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(&data->forks[second_fork]);
    print_status(philo, "has taken a fork");
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
	precise_usleep(data->time_to_eat * 1000);
	pthread_mutex_lock(&data->dead_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->dead_mutex);
}
