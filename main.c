/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:03:06 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/24 12:28:38 by lihrig           ###   ########.fr       */
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

int main(int argc, char* argv[])
{
    t_data *data;
    t_philosophers *philosophers;
    pthread_t monitor_thread;
    int i;
    
    data = NULL;
    philosophers = NULL;
    if(argc < 5 || argc > 6)
        return (print_instructions(), 1);
    
    data = init_data(argc, argv);
    if(!data)
        return 1;      
    
    philosophers = init_philosophers(data);
    if(!philosophers)
    {
        free_data(data);
        return 1;
    }
    
    // Create philosopher threads
    i = 0;
    while (i < data->nbr_philosophers)
    {
        if (pthread_create(&philosophers[i].thread, NULL, philosopher_routine, &philosophers[i]) != 0)
        {
            printf("Error creating thread for philosopher %d\n", i);
            free_philosophers(philosophers);
            free_data(data);
            return 1;
        }
        i++;
    }
    
    // Create monitor thread
    if (pthread_create(&monitor_thread, NULL, monitor_routine, philosophers) != 0)
    {
        printf("Error creating monitor thread\n");
        free_philosophers(philosophers);
        free_data(data);
        return 1;
    }
    
    // Wait for all threads to finish
    i = 0;
    while (i < data->nbr_philosophers)
    {
        pthread_join(philosophers[i].thread, NULL);
        i++;
    }
    pthread_join(monitor_thread, NULL);
    
    free_philosophers(philosophers);
    free_data(data);
    return 0;
}
