/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:03:25 by lihrig            #+#    #+#             */
/*   Updated: 2025/04/15 17:10:09 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>

typedef struct s_philosophers
{
	int				id;
	pthread_t		thread;
	int				le_fork_index;
	int				re_fork_index;
	long			last_meal;
	struct s_data	*data;

}				t_philosophers;
