/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:22:04 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/09 11:37:00 by thmeyer          ###   ########.fr       */
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

static void	odd_routine(t_philo *philo)
{
}

static void	even_routine(t_philo *philo)
{
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nbr_must_eat == -1)
	{
		if (philo->id % 2 == 0)
		{
			while (1)
			{
				pthread_mutex_lock(&philo->data->mutex_data);
				if (!philo->data->all_alive)
					return (pthread_mutex_unlock(&philo->data->mutex_data), \
					NULL);
				pthread_mutex_unlock(&philo->data->mutex_data);
				if (philo->id % 2 == 0)
					usleep((philo->data->time_to_eat - \
					(philo->data->time_to_eat / 10)) * 1000);
				forks_and_eat(philo, philo->data);
			}
		}
	}
	else
		delimited_routine(philo, philo->data);
	return (NULL);
}
