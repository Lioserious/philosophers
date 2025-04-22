/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:03:06 by lihrig            #+#    #+#             */
/*   Updated: 2025/04/22 14:49:43 by lihrig           ###   ########.fr       */
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
	memset(data, 0, sizeof(t_data));
	free(data);
}
void free_philisophers(t_philosophers *philosophers)
{
	if(!philosophers)
		return;
	memset(philosophers, 0, sizeof(philosophers));
	free(philosophers);
}

int main (int argc, char* argv[])
{
	t_data *data;
	t_philosophers *philosophers;
	if(argc < 5 || argc > 6)
	{
		data = init_data(argc, argv);
		if(!data)
			return(free_data(data), 1);
		philosophers = init_philosophers(data);
		if(!philosophers)
			return(free_data(data),free_philisophers(philosophers), 1);
	}
	free_philisophers(philosophers);
	free_data(data);
	print_instructions;
}
