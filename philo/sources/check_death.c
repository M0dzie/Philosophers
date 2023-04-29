/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:50:33 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/29 16:21:51 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	check_death(t_philo *philo)
{
	int				i;
	long			time_eat;
	struct timeval	now;

	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex_data);
		if (philo->data->all_alive == 2)
			return ((void)pthread_mutex_unlock(&philo->data->mutex_data));
		pthread_mutex_unlock(&philo->data->mutex_data);
		i = -1;
		while (++i < philo->data->nbr_philo)
		{
			gettimeofday(&now, NULL);
			time_eat = (now.tv_sec - philo[i].last_eat.tv_sec) * 1000 + \
			(now.tv_usec - philo[i].last_eat.tv_usec) / 1000;
			if (time_eat > philo->data->time_to_die)
				return (display_status(&philo[i], 4), \
pthread_mutex_lock(&philo->data->mutex_data), philo->data->all_alive = 0, \
(void)pthread_mutex_unlock(&philo->data->mutex_data));
		}
		usleep(1000);
	}
}
