/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:26:14 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/24 12:49:48 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *philosopher_routine(void *arg)
{
    t_philosophers *philosophers;
    t_data *data;

    philosophers = (t_philosophers *)arg;
    data = philosophers->data;
    
    // Special case for single philosopher - they will starve
    if (data->nbr_philosophers == 1)
    {
        print_status(philosophers, "is thinking");
        usleep(data->time_to_think * 1000);
        print_status(philosophers, "has taken a fork");
        // Can't take second fork, so just wait to die
        usleep(data->time_to_die * 1000 + 1000);
        return (NULL);
    }
    
    if (philosophers->id % 2 == 0)
        usleep(1000);
        
    while (1)
    {
        pthread_mutex_lock(&data->dead_mutex);
        if (data->is_dead)
        {
            pthread_mutex_unlock(&data->dead_mutex);
            break ;
        }
        pthread_mutex_unlock(&data->dead_mutex);
        
        print_status(philosophers, "is thinking");
        usleep(data->time_to_think * 1000);
        
        if (philosophers->id % 2 == 0)
        {
            pthread_mutex_lock(&data->forks[philosophers->le_fork_index]);
            print_status(philosophers, "has taken a fork");
            pthread_mutex_lock(&data->forks[philosophers->re_fork_index]);
            print_status(philosophers, "has taken a fork");
        }
        else
        {
            pthread_mutex_lock(&data->forks[philosophers->re_fork_index]);
            print_status(philosophers, "has taken a fork");
            pthread_mutex_lock(&data->forks[philosophers->le_fork_index]);
            print_status(philosophers, "has taken a fork");
        }
        
        print_status(philosophers, "is eating");
        pthread_mutex_lock(&data->dead_mutex);
        philosophers->last_meal = get_current_time();
        pthread_mutex_unlock(&data->dead_mutex);
        usleep(data->time_to_eat * 1000);
        
        pthread_mutex_lock(&data->dead_mutex);
        philosophers->meals_eaten++;
        pthread_mutex_unlock(&data->dead_mutex);
        
        pthread_mutex_unlock(&data->forks[philosophers->le_fork_index]);
        pthread_mutex_unlock(&data->forks[philosophers->re_fork_index]);
        
        print_status(philosophers, "is sleeping");
        usleep(data->time_to_sleep * 1000);
    }
    return (NULL);
}
