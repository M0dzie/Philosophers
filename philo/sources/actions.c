/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:43:45 by thmeyer           #+#    #+#             */
/*   Updated: 2023/05/04 10:03:52 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	thinking(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->mutex_data);
	if (data->all_alive)
	{
		pthread_mutex_unlock(&data->mutex_data);
		display_status(philo, 0);
	}
	else
		pthread_mutex_unlock(&data->mutex_data);
}

static void	take_forks(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->fork[philo->id - 1]);
	pthread_mutex_lock(&data->mutex_data);
	if (data->all_alive)
	{
		pthread_mutex_unlock(&data->mutex_data);
		display_status(philo, 1);
	}
	else
		pthread_mutex_unlock(&data->mutex_data);
	if (data->nbr_philo > 1)
	{
		pthread_mutex_lock(&data->fork[philo->id % data->nbr_philo]);
		pthread_mutex_lock(&data->mutex_data);
		if (data->all_alive)
		{
			pthread_mutex_unlock(&data->mutex_data);
			display_status(philo, 1);
		}
		else
			pthread_mutex_unlock(&data->mutex_data);
	}
	else
		usleep(data->time_to_die * 1000);
}

static void	eating(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->mutex_data);
	if (data->all_alive)
	{
		pthread_mutex_unlock(&data->mutex_data);
		display_status(philo, 2);
		usleep(data->time_to_eat * 1000);
	}
	else
		pthread_mutex_unlock(&data->mutex_data);
	pthread_mutex_lock(&philo->mutex_philo);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->mutex_philo);
}

static void	sleeping(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->mutex_data);
	if (data->all_alive)
	{
		pthread_mutex_unlock(&data->mutex_data);
		display_status(philo, 3);
		usleep(data->time_to_sleep * 1000);
	}
	else
		pthread_mutex_unlock(&data->mutex_data);
}

void	forks_and_eat(t_philo *philo)
{
	thinking(philo, philo->data);
	take_forks(philo, philo->data);
	eating(philo, philo->data);
	pthread_mutex_unlock(&philo->data->fork[philo->id - 1]);
	if (philo->data->nbr_philo > 1)
		pthread_mutex_unlock(&philo->data->fork[philo->id % \
		philo->data->nbr_philo]);
	sleeping(philo, philo->data);
}
