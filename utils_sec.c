/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:17:37 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/24 13:53:23 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_instructions(void)
{
	printf("The Programm takes the arguments in the following Order\n");
	printf("programm [Number of Philosophers] [time to die] [time to eat]");
	printf(" [time to sleep] Optional:[meals he has to eat]\n");
}

void	free_data(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->forks)
	{
		i = 0;
		while (i < data->nbr_philosophers)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	ft_memset(data, 0, sizeof(t_data));
	free(data);
}

void	free_philosophers(t_philosophers *philosophers)
{
	if (!philosophers)
		return ;
	ft_memset(philosophers, 0, sizeof(philosophers));
	free(philosophers);
}

/**
 * Counts how many philosophers have eaten the required number of meals.
 * Thread-safe iteration through all philosophers checking their meal count.
 * Returns the number of philosophers who have completed their meals.
 */
int	count_satisfied_philosophers(t_philosophers *philosophers, t_data *data)
{
	int	i;
	int	satisfied_count;

	i = 0;
	satisfied_count = 0;
	while (i < data->nbr_philosophers)
	{
		pthread_mutex_lock(&data->dead_mutex);
		if (philosophers[i].meals_eaten >= data->forced_to_eat)
			satisfied_count++;
		pthread_mutex_unlock(&data->dead_mutex);
		i++;
	}
	return (satisfied_count);
}
