/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:50:33 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/02 11:37:24 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	special_case(t_philo *philo)
{
	if (philo->data->nbr_philo == 1)
	{
		usleep(philo->data->time_to_die);
		display_status(&philo[0], 4);
		return (1);
	}
	else
	{
		pthread_mutex_lock(&philo->data->mutex_data);
		if (philo->data->all_alive == 2)
			return (pthread_mutex_unlock(&philo->data->mutex_data), 1);
		pthread_mutex_unlock(&philo->data->mutex_data);
	}
	return (0);
}

void	check_death(t_philo *philo)
{
	int				i;
	long			time_eat;
	long			cur_time;

	while (1)
	{
		if (special_case(philo))
			return ;
		i = -1;
		while (++i < philo->data->nbr_philo)
		{
			cur_time = get_time();
			pthread_mutex_lock(&philo[i].mutex_philo);
			time_eat = cur_time - philo[i].last_eat;
			pthread_mutex_unlock(&philo[i].mutex_philo);
			if (time_eat > philo->data->time_to_die)
				return (display_status(&philo[i], 4), \
pthread_mutex_lock(&philo->data->mutex_data), philo->data->all_alive = 0, \
	(void)pthread_mutex_unlock(&philo->data->mutex_data));
		}
		usleep(1000);
	}
}
