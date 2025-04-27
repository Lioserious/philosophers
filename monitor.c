/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:38:41 by lihrig            #+#    #+#             */
/*   Updated: 2025/04/27 15:58:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_if_philosopher_died(t_philosophers *philosophers, int index)
{
    t_data *data;
    
    data = philosophers[0].data;
    pthread_mutex_lock(&data->dead_mutex);
    if ((get_current_time() - philosophers[index].last_meal) > data->time_to_die)
    {
        data->is_dead = 1;
        print_status(&philosophers[index], "died");
        pthread_mutex_unlock(&data->dead_mutex);
        return (1);
    }
    pthread_mutex_unlock(&data->dead_mutex);
    return (0);
}

int check_if_all_ate_enough(t_philosophers *philosophers)
{
    t_data *data;
    int i;
    int all_ate_enough;
    
    data = philosophers[0].data;
    i = 0;
    all_ate_enough = 1;
    
    if (data->forced_to_eat <= 0)
        return (0);
    while (i < data->nbr_philosophers)
    {
        pthread_mutex_lock(&data->dead_mutex);
        if (philosophers[i].meals_eaten < data->forced_to_eat)
            all_ate_enough = 0;
        pthread_mutex_unlock(&data->dead_mutex);
        i++;
    }
    pthread_mutex_lock(&data->dead_mutex);
    if (all_ate_enough)
    {
        data->is_dead = 1;
        return (pthread_mutex_unlock(&data->dead_mutex),1);
    }
    return (pthread_mutex_unlock(&data->dead_mutex), 0);
}

void *monitor_routine(void *arg)
{
    t_philosophers *philosophers;
    int i;
    
    philosophers = (t_philosophers *)arg;
    
    while (1)
    {
        i = 0;
        while (i < philosophers[0].data->nbr_philosophers)
        {
            if (check_if_philosopher_died(philosophers, i))
                return (NULL);
            i++;
        }
        if (check_if_all_ate_enough(philosophers))
            return (NULL);
        usleep(1000);
    }
    return (NULL);
}
