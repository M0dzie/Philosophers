/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:22:04 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/11 15:51:26 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	start_routine(t_philo *philo, t_data *data, int odd)
{
	while (1)
	{
		pthread_mutex_lock(&data->mutex_data);
		if (!data->all_alive || philo->eat_count == data->nbr_must_eat)
		{
			if (philo->eat_count == data->nbr_must_eat)
				data->all_alive = 2;
			return ((void)pthread_mutex_unlock(&data->mutex_data));
		}
		pthread_mutex_unlock(&data->mutex_data);
		if (!philo->ate)
		{
			if (philo->id == 3 && data->nbr_philo == 3)
				usleep((data->time_to_eat * 0.9) * 1200);
			if (philo->id % 2 == 0 && odd)
				usleep((data->time_to_eat * 0.9) * 1000);
			forks_and_eat(philo, data);
			pthread_mutex_lock(&philo->mutex_philo);
			philo->eat_count++;
			pthread_mutex_unlock(&philo->mutex_philo);
		}
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nbr_philo % 2 == 0 || philo->data->nbr_philo > 15 || \
	philo->data->nbr_philo == 1)
	{
		if (philo->id % 2 == 0)
			usleep((philo->data->time_to_eat * 0.9) * 1000);
		start_routine(philo, philo->data, 0);
	}
	else
		start_routine(philo, philo->data, 1);
	return (NULL);
}
