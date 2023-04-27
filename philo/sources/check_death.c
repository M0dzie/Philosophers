/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:50:33 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/27 11:24:32 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	lock_mutex_philo(t_philo *philo, int lock)
{
	int	i;

	i = -1;
	if (lock)
		while (++i < philo->data->nbr_philo)
			pthread_mutex_lock(&philo[i].mutex_philo);
	if (!lock)
		while (++i < philo->data->nbr_philo)
			pthread_mutex_unlock(&philo[i].mutex_philo);
}

void	check_death(t_philo *philo)
{
	int				i;
	long			time_eat;
	struct timeval	now;

	while (1)
	{
		i = -1;
		while (++i < philo->data->nbr_philo)
		{
			gettimeofday(&now, NULL);
			time_eat = (now.tv_sec - philo[i].last_eat.tv_sec) * 1000 + \
			(now.tv_usec - philo[i].last_eat.tv_usec) / 1000;
			if (time_eat > philo->data->time_to_die)
			{
				display_status(&philo[i], 4);
				lock_mutex_philo(philo, 1);
				i = -1;
				while (++i < philo->data->nbr_philo)
					philo[i].is_alive = 0;
				lock_mutex_philo(philo, 0);
				return ;
			}
		}
		usleep(1000);
	}
}
