/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:18:06 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/24 14:03:44 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	if (!data->is_dead)
	{
		current_time = get_current_time();
		elapsed_time = current_time - data->start_time;
		printf("%ld %d %s\n", elapsed_time, philo->id + 1, status);
	}
	pthread_mutex_unlock(&data->dead_mutex);
	pthread_mutex_unlock(&data->write_mutex);
}

void	*ft_memset(void *ptr, int value, size_t nbr)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)ptr;
	i = 0;
	while (i < nbr)
	{
		p[i] = (unsigned char)value;
		i++;
	}
	return (ptr);
}
