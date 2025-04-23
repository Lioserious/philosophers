/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:18:06 by lihrig            #+#    #+#             */
/*   Updated: 2025/04/23 16:16:47 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;
	int		i;

	i = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		NULL;
	data->nbr_philosophers = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->time_to_think = 100;
	if (argc == 6)
		data->forced_to_eat = atoi(argv[5]);
	else
		data->forced_to_eat = 0;
	data->is_dead = 0;
	data->start_time = get_current_time();
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philosophers);
	if (!data->forks)
		return (NULL);
	while (i < data->nbr_philosophers)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	return (data);
}
t_philosophers	*init_philosophers(t_data *data)
{
	t_philosophers	*philosophers;
	int				i;

	i = 0;
	philosophers = malloc(sizeof(t_philosophers) * data->nbr_philosophers);
	if (!philosophers)
		return (NULL);
	while (i < data->nbr_philosophers)
	{
		philosophers[i].id = i;
		philosophers[i].le_fork_index = i;
		philosophers[i].re_fork_index = (i + 1) % data->nbr_philosophers;
		philosophers[i].last_meal = data->start_time;
		philosophers[i].meals_eaten = 0;
		philosophers[i].data = data;
		i++;
	}
	return (philosophers);
}

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_status(t_philosophers *philo, char *status)
{
	t_data	*data;
	long	current_time;
	long	elapsed_time;

	data = philo->data;
	pthread_mutex_lock(&data->write_mutex);
	pthread_mutex_lock(&data->dead_mutex);
	pthread_mutex_unlock(&data->dead_mutex);
	if (!data->is_dead)
	{
		current_time = get_current_time();
		elapsed_time = current_time - data->start_time;
		printf("%ld %d %s\n", elapsed_time, philo->id + 1, status);
	}
	pthread_mutex_unlock(&data->write_mutex);
}

void	*ft_memset(void *ptr, int value, size_t nbr)
{
	unsigned char *p;
	size_t i;

	p = (unsigned char *)ptr;
	i = 0;
	while (i < nbr)
	{
		p[i] = (unsigned char)value;
		i++;
	}
	return (ptr);
}