/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:17:37 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/24 13:44:35 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void print_instructions()
{
	printf("The Programm takes the arguments in the following Order\n");
	printf("programm [Number of Philosophers] [time to die] [time to eat]");
	printf(" [time to sleep] Optional:[meals he has to eat]\n");
}

void free_data(t_data *data)
{
	int i;
	if(!data)
		return;
	if(data->forks)
	{
		i = 0;
		while(i < data->nbr_philosophers)
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

void free_philosophers(t_philosophers *philosophers)
{
	if(!philosophers)
		return;
	ft_memset(philosophers, 0, sizeof(philosophers));
	free(philosophers);
}
