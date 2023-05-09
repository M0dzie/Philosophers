/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:22:04 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/09 15:58:12 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	delimited_routine(t_philo *philo, t_data *data)
{
	int	eat_count;

	eat_count = 0;
	while (1)
	{
		pthread_mutex_lock(&data->mutex_data);
		if (!data->all_alive)
			return ((void)pthread_mutex_unlock(&data->mutex_data));
		pthread_mutex_unlock(&data->mutex_data);
		forks_and_eat(philo, data);
		eat_count++;
		if (eat_count == data->nbr_must_eat)
		{
			pthread_mutex_lock(&data->mutex_data);
			data->all_alive = 2;
			pthread_mutex_unlock(&data->mutex_data);
			return ;
		}
	}
}

// static void	display_routine(t_philo *philo, t_data *data, int even)
// {
// 	while (1)
// 	{
// 		pthread_mutex_lock(&data->mutex_data);
// 		if (!data->all_alive || philo->eat_count == data->nbr_philo)
// 		{
// 			if (philo->eat_count == data->nbr_philo)
// 				data->all_alive = 2;
// 			return ((void)pthread_mutex_unlock(&data->mutex_data));
// 		}
// 		pthread_mutex_unlock(&data->mutex_data);
// 		if (!philo->ate)
// 		{
// 			if (philo->id == 3 && data->nbr_philo == 3)
// 				usleep(data->time_to_eat * 1000);
// 			if (philo->id % 2 == 0 && !even)
// 				usleep(data->time_to_eat * 900);
// 			forks_and_eat(philo, data);
// 			pthread_mutex_lock(&philo->mutex_philo);
// 			philo->eat_count++;
// 			pthread_mutex_unlock(&philo->mutex_philo);
// 		}
// 	}
// }

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 900);
	if (philo->data->nbr_must_eat == -1)
	{
		while (1)
		{
			pthread_mutex_lock(&philo->data->mutex_data);
			if (!philo->data->all_alive)
				return (pthread_mutex_unlock(&philo->data->mutex_data), NULL);
			pthread_mutex_unlock(&philo->data->mutex_data);
			forks_and_eat(philo, philo->data);
		}
	}
	else
		delimited_routine(philo, philo->data);
	// if (philo->data->nbr_philo % 2 == 0 || philo->data->nbr_philo > 15 || philo->data->nbr_philo == 1)
	// {
	// 	if (philo->id % 2 == 0)
	// 		usleep(philo->data->time_to_eat * 900);
	// 	display_routine(philo, philo->data, 1);
	// }
	// else
	// 	display_routine(philo, philo->data, 0);
	return (NULL);
}
