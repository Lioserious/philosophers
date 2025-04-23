/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:26:14 by lihrig            #+#    #+#             */
/*   Updated: 2025/04/23 16:17:53 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosopher_routine(void *arg)
{
	t_philosophers	*philosophers;
	t_data			*data;

	philosophers = (t_philosophers *)arg;
	data = philosophers->data;
	if (philosophers->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (data->is_dead)
		{
			pthread_mutex_lock(&data->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->dead_mutex);
		print_status(philosophers, "is thinking");
		usleep(data->time_to_think * 1000);
		if (philosophers->id % 2 == 0)
		{
			pthread_mutex_lock(&data->forks[philosophers->le_fork_index]);
			print_status(philosophers, "has taken le fork");
			pthread_mutex_lock(&data->forks[philosophers->re_fork_index]);
			print_status(philosophers, "has taken re fork");
		}
		else
		{
			pthread_mutex_lock(&data->forks[philosophers->re_fork_index]);
			print_status(philosophers, "has taken re fork");
			pthread_mutex_lock(&data->forks[philosophers->le_fork_index]);
			print_status(philosophers, "has taken le fork");
		}
		print_status(philosophers, "is eating");
		philosophers->last_meal = get_current_time();
		usleep(data->time_to_eat * 1000);
		philosophers->meals_eaten++;
		pthread_mutex_unlock(&data->forks[philosophers->le_fork_index]);
		pthread_mutex_unlock(&data->forks[philosophers->re_fork_index]);
		print_status(philosophers, "is sleeping");
		usleep(data->time_to_sleep * 1000);
	}
	return (NULL);
}
