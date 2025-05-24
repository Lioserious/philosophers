/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:26:14 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/24 13:29:11 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Releases both forks after eating is complete.
 * Forks are released in the same order regardless of acquisition order.
 */
static void release_forks(t_philosophers *philo)
{
    t_data *data;
    
    data = philo->data;
    pthread_mutex_unlock(&data->forks[philo->le_fork_index]);
    pthread_mutex_unlock(&data->forks[philo->re_fork_index]);
}

/**
 * Handles the sleeping phase of a philosopher's life cycle.
 * Prints sleeping status and sleeps for the designated sleeping time.
 */
static void sleep_phase(t_philosophers *philo)
{
    print_status(philo, "is sleeping");
    usleep(philo->data->time_to_sleep * 1000);
}

/**
 * Main routine executed by each philosopher thread.
 * Manages the complete lifecycle: thinking -> eating -> sleeping.
 * Handles special case for single philosopher and implements deadlock prevention.
 */
void *philosopher_routine(void *arg)
{
    t_philosophers *philo;
    t_data *data;

    philo = (t_philosophers *)arg;
    data = philo->data;
    if (data->nbr_philosophers == 1)
    {
        handle_single_philosopher(philo);
        return (NULL);
    }
    if (philo->id % 2 == 0)
        usleep(1000);
    while (1)
    {
        if (should_stop_simulation(data))
            break;
        think_phase(philo);
        acquire_forks(philo);
        eat_phase(philo);
        release_forks(philo);
        sleep_phase(philo);
    }
    return (NULL);
}
