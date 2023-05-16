/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:22:04 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/16 10:25:02 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	start_routine(t_philo *philo, long time_to_eat, long nbr_philo, \
int odd)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex_data);
		if (!philo->data->all_alive || philo->eat_count == \
		philo->data->nbr_must_eat)
			return ((void)pthread_mutex_unlock(&philo->data->mutex_data));
		pthread_mutex_unlock(&philo->data->mutex_data);
		if (!philo->ate)
		{
			if (philo->id == 3 && nbr_philo == 3)
				usleep((time_to_eat * 0.9) * 1200);
			if (philo->id % 2 == 0 && odd)
				usleep((time_to_eat * 0.9) * 1000);
			actions(philo, philo->data, nbr_philo);
			pthread_mutex_lock(&philo->mutex_philo);
			philo->eat_count++;
			pthread_mutex_unlock(&philo->mutex_philo);
		}
	}
}

void	*routine(void *arg)
{
	long	time_to_eat;
	long	nbr_philo;
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->mutex_data);
	time_to_eat = philo->data->time_to_eat;
	nbr_philo = philo->data->nbr_philo;
	pthread_mutex_unlock(&philo->data->mutex_data);
	if (nbr_philo % 2 == 0 || nbr_philo == 1)
	{
		if (philo->id % 2 == 0)
			usleep((time_to_eat * 0.9) * 1000);
		start_routine(philo, time_to_eat, nbr_philo, 0);
	}
	else
	{
		if (nbr_philo == 3)
			start_routine(philo, time_to_eat, nbr_philo, 1);
		if (philo->id % 2 == 0)
			usleep((time_to_eat * 0.9) * 1000);
		start_routine(philo, time_to_eat, nbr_philo, 0);
	}
	return (NULL);
}
