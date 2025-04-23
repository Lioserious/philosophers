/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:38:41 by lihrig            #+#    #+#             */
/*   Updated: 2025/04/23 17:51:27 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *monitor_routine(void *arg)
{
    t_philosophers *philosophers;
    t_data *data;
    int i;
    int all_ate_enough;
    
    philosophers = (t_philosophers *)arg;
    data = philosophers[0].data;
    
    while (1)
	{
		i = 0;
		all_ate_enough = 1;
		while(i < data->nbr_philosophers)
		{
			pthread_mutex_lock(data->dead_mutex);
			if ((get_current_time() - philosophers[i].last_meal) > data->time_to_die)
			{
				data->is_dead = 1;
				print_status(&philosophers[i])
			}
		}
		
	}

	
}