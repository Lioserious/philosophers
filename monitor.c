/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:38:41 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/29 16:54:35 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_if_philosopher_died(t_philosophers *philosophers, int index)
{
	t_data	*data;
	long	current_time;
	long	elapsed_time;

	data = philosophers[0].data;
	pthread_mutex_lock(&data->dead_mutex);
	if ((get_current_time()
			- philosophers[index].last_meal) > data->time_to_die)
	{
		data->is_dead = 1;
		pthread_mutex_lock(&data->write_mutex);
		current_time = get_current_time();
		elapsed_time = current_time - data->start_time;
		printf("%ld %d died\n", elapsed_time, philosophers[index].id + 1);
		pthread_mutex_unlock(&data->write_mutex);
		pthread_mutex_unlock(&data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_mutex);
	return (0);
}

static void	print_completion_message(t_data *data)
{
	long	current_time;
	long	elapsed_time;

	pthread_mutex_lock(&data->write_mutex);
	current_time = get_current_time();
	elapsed_time = current_time - data->start_time;
	printf("%ld ALLE SIND SATT %d times each. Simulation complete!\n",
		elapsed_time, data->forced_to_eat);
	pthread_mutex_unlock(&data->write_mutex);
}

/**
 * Marks the simulation as complete and triggers termination.
 * Sets the global death flag and prints completion message.
 */
static void	end_simulation_successfully(t_data *data)
{
	data->is_dead = 1;
	print_completion_message(data);
}

/**
 * Checks if all philosophers have eaten the required number of meals.
 * Returns 1 if simulation should end due to completion,
	0 if it should continue.
 * Handles the case where no meal limit is set (forced_to_eat <= 0).
 */
int	check_if_all_ate_enough(t_philosophers *philosophers)
{
	t_data	*data;
	int		satisfied_count;

	data = philosophers[0].data;
	if (data->forced_to_eat <= 0)
		return (0);
	satisfied_count = count_satisfied_philosophers(philosophers, data);
	pthread_mutex_lock(&data->dead_mutex);
	if (satisfied_count == data->nbr_philosophers)
	{
		end_simulation_successfully(data);
		pthread_mutex_unlock(&data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_mutex);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philosophers	*philosophers;
	int				i;

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
		usleep(100);
	}
	return (NULL);
}
